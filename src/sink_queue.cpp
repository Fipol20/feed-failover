#include "feed/sink_queue.hpp"

namespace feed {

SinkQueue::SinkQueue(std::size_t capacity) : capacity_(capacity) {}

bool SinkQueue::evict_oldest_data() {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (!is_alert(*it)) {
            items_.erase(it);
            return true;
        }
    }
    return false;
}

bool SinkQueue::push(const Frame& frame) {
    if (capacity_ == 0) {
        return false;
    }
    if (items_.size() < capacity_) {
        items_.push_back(frame);
        return true;
    }
    if (is_alert(frame) && evict_oldest_data()) {
        items_.push_back(frame);
        return true;
    }
    return false;
}

std::optional<Frame> SinkQueue::pop() {
    if (items_.empty()) {
        return std::nullopt;
    }
    Frame front = items_.front();
    items_.pop_front();
    return front;
}

std::size_t SinkQueue::size() const {
    return items_.size();
}

std::size_t SinkQueue::capacity() const {
    return capacity_;
}

}  // namespace feed
