#include "check.hpp"
#include "feed/source_selector.hpp"

namespace {

feed::Frame frame_at(std::uint64_t seq, std::uint64_t ts) {
    feed::Frame frame;
    frame.seq = seq;
    frame.timestamp_ms = ts;
    return frame;
}

}  // namespace

void test_selector() {
    feed::SourceSelector selector(200);

    selector.push_primary(frame_at(1, 1000));
    selector.push_backup(frame_at(50, 1000));

    auto first = selector.select(1050);
    CHECK(first.has_value());
    CHECK(first->source == feed::ActiveSource::Primary);
    CHECK(first->frame.seq == 1);

    // primary замолчал, backup продолжает слать свои кадры со своей нумерацией
    selector.push_backup(frame_at(50, 1250));
    auto after = selector.select(1300);
    CHECK(after.has_value());
    CHECK(after->source == feed::ActiveSource::Backup);
    CHECK(after->frame.seq == 50);
    CHECK(after->frame.seq != first->frame.seq + 1);

    selector.push_backup(frame_at(51, 1000));
    auto none = selector.select(1400);
    CHECK(!none.has_value());
    CHECK(selector.active() == feed::ActiveSource::None);
}
