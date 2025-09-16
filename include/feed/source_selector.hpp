#pragma once

#include "feed/frame.hpp"

#include <optional>

namespace feed {

enum class ActiveSource { Primary, Backup, None };

struct Selected {
    Frame frame;
    ActiveSource source = ActiveSource::None;
};

// Пока primary даёт свежие кадры - берём его. Иначе backup.
// Если оба молчат или оба протухли - None (на индикаторе будет NO_DATA).
//
// seq у источников независимые: при переключении не пытаемся "продолжить"
// нумерацию primary на backup.
class SourceSelector {
public:
    explicit SourceSelector(std::uint64_t stale_ms);

    void push_primary(const Frame& frame);
    void push_backup(const Frame& frame);

    std::optional<Selected> select(std::uint64_t now_ms);
    ActiveSource active() const;

private:
    bool usable(const std::optional<Frame>& slot, std::uint64_t now_ms) const;

    std::uint64_t stale_ms_;
    std::optional<Frame> primary_;
    std::optional<Frame> backup_;
    ActiveSource active_ = ActiveSource::None;
};

const char* to_string(ActiveSource source);

}  // namespace feed
