#pragma once

#include <cstdint>

namespace feed {

// Учебный кадр. Поля payload выдуманы для демо, это не параметры какого-то
// реального устройства.
enum class FrameKind { Data, Alert };

struct Payload {
    double heading_deg = 0.0;
    double altitude_m = 0.0;
    bool alert = false;
};

struct Frame {
    std::uint64_t seq = 0;
    std::uint64_t timestamp_ms = 0;
    FrameKind kind = FrameKind::Data;
    Payload payload{};
};

bool is_alert(const Frame& frame);
bool is_stale(const Frame& frame, std::uint64_t now_ms, std::uint64_t stale_ms);

}  // namespace feed
