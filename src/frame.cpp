#include "feed/frame.hpp"

namespace feed {

bool is_alert(const Frame& frame) {
    return frame.kind == FrameKind::Alert || frame.payload.alert;
}

bool is_stale(const Frame& frame, std::uint64_t now_ms, std::uint64_t stale_ms) {
    if (now_ms < frame.timestamp_ms) {
        // часы уехали назад - считаем кадр сомнительным, лучше не показывать
        return true;
    }
    return (now_ms - frame.timestamp_ms) > stale_ms;
}

}  // namespace feed
