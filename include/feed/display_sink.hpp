#pragma once

#include "feed/source_selector.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace feed {

// Последняя показанная страница + фильтр повторов seq в рамках одного источника.
class DisplaySink {
public:
    bool accept(const Selected& selected);
    std::string render(const std::optional<Selected>& selected) const;

    std::uint64_t replay_drops() const { return replay_drops_; }
    std::uint64_t gap_count() const { return gap_count_; }
    const std::string& last_page() const { return last_page_; }

private:
    static std::string format(const Selected& selected);

    std::optional<ActiveSource> last_source_;
    std::optional<std::uint64_t> last_seq_;
    std::uint64_t replay_drops_ = 0;
    std::uint64_t gap_count_ = 0;
    std::string last_page_;
};

}  // namespace feed
