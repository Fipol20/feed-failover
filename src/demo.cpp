#include "feed/display_sink.hpp"
#include "feed/source_selector.hpp"

#include <iostream>

namespace {

feed::Frame make_frame(std::uint64_t seq, std::uint64_t now_ms, double heading, double altitude) {
    feed::Frame frame;
    frame.seq = seq;
    frame.timestamp_ms = now_ms;
    frame.payload.heading_deg = heading;
    frame.payload.altitude_m = altitude;
    return frame;
}

}  // namespace

int main() {
    const std::uint64_t stale_ms = 150;
    const std::uint64_t tick_ms = 50;
    const int primary_dies_after = 12;

    feed::SourceSelector selector(stale_ms);
    feed::DisplaySink sink;

    std::uint64_t now = 1000;
    std::uint64_t primary_seq = 1;
    std::uint64_t backup_seq = 100;  // другая нумерация специально

    std::cout << "tick source page\n";

    for (int tick = 0; tick < 24; ++tick) {
        if (tick < primary_dies_after) {
            selector.push_primary(make_frame(primary_seq, now, 10.0 + tick, 100.0 + tick));
            ++primary_seq;
        }
        selector.push_backup(make_frame(backup_seq, now, 40.0 + tick, 200.0 + tick));
        ++backup_seq;

        auto selected = selector.select(now);
        std::string page = sink.render(selected);
        if (selected && sink.accept(*selected)) {
            page = sink.last_page();
        } else if (selected) {
            page = sink.last_page() + " (hold)";
        }

        std::cout << tick << " " << feed::to_string(selector.active()) << " " << page << "\n";
        now += tick_ms;
    }
    return 0;
}
