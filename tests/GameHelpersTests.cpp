#include "TestHarness.h"

#include "../GameHelpers.h"

TEST_CASE(clamp_paddle_position_returns_left_bound_when_value_is_too_small) {
    CHECK_EQ(GameHelpers::clampPaddlePosition(10.f, 20.f, 100.f), 20.f);
}

TEST_CASE(clamp_paddle_position_returns_right_bound_when_value_is_too_large) {
    CHECK_EQ(GameHelpers::clampPaddlePosition(120.f, 20.f, 100.f), 100.f);
}

TEST_CASE(clamp_paddle_position_keeps_value_within_bounds) {
    CHECK_EQ(GameHelpers::clampPaddlePosition(60.f, 20.f, 100.f), 60.f);
}

TEST_CASE(decrement_life_reduces_positive_life_count) {
    CHECK_EQ(GameHelpers::decrementLife(3), 2);
}

TEST_CASE(decrement_life_clamps_zero) {
    CHECK_EQ(GameHelpers::decrementLife(0), 0);
}

TEST_CASE(has_remaining_bricks_is_true_for_positive_counts) {
    CHECK(GameHelpers::hasRemainingBricks(1));
}

TEST_CASE(has_remaining_bricks_is_false_for_zero) {
    CHECK(!GameHelpers::hasRemainingBricks(0));
}
