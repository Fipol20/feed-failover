#include "check.hpp"
#include "feed/display_sink.hpp"

void test_seq() {
    feed::DisplaySink sink;
    feed::Selected a;
    a.source = feed::ActiveSource::Primary;
    a.frame.seq = 3;
    a.frame.timestamp_ms = 1000;

    CHECK(sink.accept(a));
    CHECK(!sink.accept(a));  // повтор того же seq
    CHECK(sink.replay_drops() == 1);

    feed::Selected gap = a;
    gap.frame.seq = 6;
    CHECK(sink.accept(gap));
    CHECK(sink.gap_count() == 1);

    // смена источника - свой seq, это не replay
    feed::Selected backup;
    backup.source = feed::ActiveSource::Backup;
    backup.frame.seq = 3;
    CHECK(sink.accept(backup));
    CHECK(sink.replay_drops() == 1);
}
