#include "check.hpp"
#include "feed/sink_queue.hpp"

namespace {

feed::Frame data(std::uint64_t seq) {
    feed::Frame frame;
    frame.seq = seq;
    return frame;
}

feed::Frame alert(std::uint64_t seq) {
    feed::Frame frame;
    frame.seq = seq;
    frame.kind = feed::FrameKind::Alert;
    frame.payload.alert = true;
    return frame;
}

}  // namespace

void test_queue() {
    feed::SinkQueue queue(2);

    CHECK(queue.push(data(1)));
    CHECK(queue.push(alert(2)));
    CHECK(!queue.push(data(3)));  // обычный кадр не вытесняет alert
    CHECK(queue.size() == 2);

    CHECK(queue.push(alert(4)));  // alert вытесняет самый старый data
    CHECK(queue.size() == 2);

    auto first = queue.pop();
    auto second = queue.pop();
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(feed::is_alert(*first));
    CHECK(feed::is_alert(*second));
    CHECK(first->seq == 2);
    CHECK(second->seq == 4);
}
