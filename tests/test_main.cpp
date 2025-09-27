#include "check.hpp"

int main() {
    test_stale();
    test_selector();
    test_seq();
    test_queue();

    if (test_failures() != 0) {
        std::cerr << test_failures() << " failed / " << test_checks() << " checks\n";
        return 1;
    }
    std::cout << test_checks() << " checks ok\n";
    return 0;
}
