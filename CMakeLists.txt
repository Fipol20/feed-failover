cmake_minimum_required(VERSION 3.16)
project(feed_failover LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(feed_core
    src/frame.cpp
    src/source_selector.cpp
    src/sink_queue.cpp
    src/display_sink.cpp
)
target_include_directories(feed_core PUBLIC include)

add_executable(feed_demo src/demo.cpp)
target_link_libraries(feed_demo PRIVATE feed_core)

enable_testing()
add_executable(feed_tests
    tests/test_main.cpp
    tests/test_stale.cpp
    tests/test_selector.cpp
    tests/test_seq.cpp
    tests/test_queue.cpp
)
target_link_libraries(feed_tests PRIVATE feed_core)
target_include_directories(feed_tests PRIVATE tests)
add_test(NAME feed_tests COMMAND feed_tests)
