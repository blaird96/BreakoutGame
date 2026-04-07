#include "TestHarness.h"

#include <exception>
#include <iostream>

int main() {
    int failed = 0;

    for (const auto& test : TestHarness::registry()) {
        try {
            test.fn();
            std::cout << "[PASS] " << test.name << '\n';
        } catch (const std::exception& ex) {
            ++failed;
            std::cout << "[FAIL] " << test.name << " - " << ex.what() << '\n';
        } catch (...) {
            ++failed;
            std::cout << "[FAIL] " << test.name << " - unknown exception\n";
        }
    }

    std::cout << "\nExecuted " << TestHarness::registry().size() << " tests, " << failed
              << " failed.\n";

    return failed == 0 ? 0 : 1;
}
