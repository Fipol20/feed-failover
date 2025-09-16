#include "feed/source_selector.hpp"

namespace feed {

SourceSelector::SourceSelector(std::uint64_t stale_ms) : stale_ms_(stale_ms) {}

void SourceSelector::push_primary(const Frame& frame) {
    primary_ = frame;
}

void SourceSelector::push_backup(const Frame& frame) {
    backup_ = frame;
}

bool SourceSelector::usable(const std::optional<Frame>& slot, std::uint64_t now_ms) const {
    return slot.has_value() && !is_stale(*slot, now_ms, stale_ms_);
}

std::optional<Selected> SourceSelector::select(std::uint64_t now_ms) {
    if (usable(primary_, now_ms)) {
        active_ = ActiveSource::Primary;
        return Selected{*primary_, ActiveSource::Primary};
    }
    if (usable(backup_, now_ms)) {
        active_ = ActiveSource::Backup;
        return Selected{*backup_, ActiveSource::Backup};
    }
    active_ = ActiveSource::None;
    return std::nullopt;
}

ActiveSource SourceSelector::active() const {
    return active_;
}

const char* to_string(ActiveSource source) {
    switch (source) {
        case ActiveSource::Primary:
            return "PRIMARY";
        case ActiveSource::Backup:
            return "BACKUP";
        case ActiveSource::None:
            return "NO_DATA";
    }
    return "NO_DATA";
}

}  // namespace feed
