#pragma once

#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace TestHarness {
struct TestCase {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(const char* name, std::function<void()> fn) {
        registry().push_back({name, std::move(fn)});
    }
};

inline std::string formatFailure(const char* expr, const char* file, int line) {
    std::ostringstream out;
    out << file << ":" << line << " CHECK failed: " << expr;
    return out.str();
}

template <typename Left, typename Right>
std::string formatEqualityFailure(const Left& left,
                                  const Right& right,
                                  const char* leftExpr,
                                  const char* rightExpr,
                                  const char* file,
                                  int line) {
    std::ostringstream out;
    out << file << ":" << line << " CHECK_EQ failed: " << leftExpr << " != " << rightExpr
        << " (" << left << " vs " << right << ")";
    return out.str();
}
}  // namespace TestHarness

#define TEST_CASE(NAME)                                                                          \
    static void test_fn_##NAME();                                                                \
    static ::TestHarness::Registrar test_registrar_##NAME(#NAME, test_fn_##NAME);               \
    static void test_fn_##NAME()

#define CHECK(EXPR)                                                                              \
    do {                                                                                         \
        if (!(EXPR)) {                                                                           \
            throw std::runtime_error(::TestHarness::formatFailure(#EXPR, __FILE__, __LINE__));  \
        }                                                                                        \
    } while (false)

#define CHECK_EQ(LEFT, RIGHT)                                                                                 \
    do {                                                                                                      \
        const auto& _left_value = (LEFT);                                                                     \
        const auto& _right_value = (RIGHT);                                                                   \
        if (!(_left_value == _right_value)) {                                                                 \
            throw std::runtime_error(::TestHarness::formatEqualityFailure(                                    \
                _left_value, _right_value, #LEFT, #RIGHT, __FILE__, __LINE__));                              \
        }                                                                                                     \
    } while (false)
