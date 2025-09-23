#include "feed/display_sink.hpp"

#include "feed/frame.hpp"

#include <sstream>

namespace feed {

bool DisplaySink::accept(const Selected& selected) {
    if (last_source_.has_value() && *last_source_ == selected.source && last_seq_.has_value()) {
        if (selected.frame.seq == *last_seq_) {
            ++replay_drops_;
            return false;
        }
        if (selected.frame.seq > *last_seq_ + 1) {
            ++gap_count_;
        }
    }
    last_source_ = selected.source;
    last_seq_ = selected.frame.seq;
    last_page_ = format(selected);
    return true;
}

std::string DisplaySink::render(const std::optional<Selected>& selected) const {
    if (!selected.has_value()) {
        return "NO_DATA";
    }
    return format(*selected);
}

std::string DisplaySink::format(const Selected& selected) {
    const Frame& frame = selected.frame;
    std::ostringstream out;
    out << to_string(selected.source)
        << " seq=" << frame.seq
        << " hdg=" << frame.payload.heading_deg
        << " alt=" << frame.payload.altitude_m;
    if (is_alert(frame)) {
        out << " ALERT";
    }
    return out.str();
}

}  // namespace feed
