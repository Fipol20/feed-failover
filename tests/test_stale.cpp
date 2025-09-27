#include "check.hpp"
#include "feed/frame.hpp"

void test_stale() {
    feed::Frame frame;
    frame.timestamp_ms = 1000;

    CHECK(!feed::is_stale(frame, 1000, 200));
    CHECK(!feed::is_stale(frame, 1200, 200));
    CHECK(feed::is_stale(frame, 1201, 200));
    CHECK(feed::is_stale(frame, 900, 200));  // часы назад - тоже не годится
}
