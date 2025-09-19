#pragma once

#include "feed/frame.hpp"

#include <cstddef>
#include <deque>
#include <optional>

namespace feed {

// Очередь на индикатор с жёстким потолком.
// Если места нет и пришёл обычный кадр - его выкидываем, алерты не трогаем.
// Если места нет и пришёл alert - вытесняем самый старый не-alert.
class SinkQueue {
public:
    explicit SinkQueue(std::size_t capacity);

    bool push(const Frame& frame);
    std::optional<Frame> pop();
    std::size_t size() const;
    std::size_t capacity() const;

private:
    bool evict_oldest_data();

    std::size_t capacity_;
    std::deque<Frame> items_;
};

}  // namespace feed
