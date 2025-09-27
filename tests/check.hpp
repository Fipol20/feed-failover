#pragma once

#include <iostream>
#include <string>

inline int& test_failures() {
    static int failures = 0;
    return failures;
}

inline int& test_checks() {
    static int checks = 0;
    return checks;
}

#define CHECK(cond)                                                                      \
    do {                                                                                 \
        ++test_checks();                                                                 \
        if (!(cond)) {                                                                   \
            ++test_failures();                                                           \
            std::cerr << __FILE__ << ":" << __LINE__ << " CHECK failed: " #cond << "\n"; \
        }                                                                                \
    } while (0)

void test_stale();
void test_selector();
void test_seq();
void test_queue();
