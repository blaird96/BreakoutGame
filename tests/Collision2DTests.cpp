#include "TestHarness.h"

#include "../src/Collision2D.h"

#include <cmath>

TEST_CASE(circle_aabb_no_hit_when_far) {
    const Collision2D::Circle c{100.f, 100.f, 10.f};
    const Collision2D::Aabb b{200.f, 200.f, 300.f, 300.f};
    CHECK(!Collision2D::circleIntersectsAabb(c, b));
    const auto r = Collision2D::resolveCircleAabb(c, b, {1.f, 0.f}, 0.01f);
    CHECK(!r.hit);
}

TEST_CASE(circle_aabb_hit_from_left_reflect_x) {
    // Ball moving right into left face of brick; dominant normal should be horizontal.
    const Collision2D::Circle c{40.f, 50.f, 10.f};
    const Collision2D::Aabb b{50.f, 40.f, 150.f, 60.f};
    CHECK(Collision2D::circleIntersectsAabb(c, b));
    const auto r = Collision2D::resolveCircleAabb(c, b, {120.f, 0.f}, 0.01f);
    CHECK(r.hit);
    CHECK(r.reflectX);
    CHECK(r.cx > c.cx);
}

TEST_CASE(circle_aabb_hit_from_top_reflect_y) {
    const Collision2D::Circle c{100.f, 35.f, 10.f};
    const Collision2D::Aabb b{50.f, 40.f, 150.f, 60.f};
    CHECK(Collision2D::circleIntersectsAabb(c, b));
    const auto r = Collision2D::resolveCircleAabb(c, b, {0.f, 80.f}, 0.01f);
    CHECK(r.hit);
    CHECK(!r.reflectX);
    CHECK(r.cy > c.cy);
}

TEST_CASE(circle_aabb_separation_clears_overlap) {
    Collision2D::Circle c{100.f, 50.f, 10.f};
    const Collision2D::Aabb b{95.f, 45.f, 130.f, 55.f};
    CHECK(Collision2D::circleIntersectsAabb(c, b));
    const auto r = Collision2D::resolveCircleAabb(c, b, {50.f, 20.f}, 0.02f);
    CHECK(r.hit);
    c.cx = r.cx;
    c.cy = r.cy;
    CHECK(!Collision2D::circleIntersectsAabb(c, b));
}

TEST_CASE(circle_aabb_multi_resolve_two_bricks) {
    Collision2D::Circle c{100.f, 50.f, 10.f};
    const Collision2D::Aabb brickA{90.f, 45.f, 98.f, 55.f};
    const Collision2D::Aabb brickB{99.f, 45.f, 108.f, 55.f};

    int hits = 0;
    for (int i = 0; i < 8; ++i) {
        bool any = false;
        if (Collision2D::circleIntersectsAabb(c, brickA)) {
            const auto r = Collision2D::resolveCircleAabb(c, brickA, {40.f, 10.f}, 0.02f);
            CHECK(r.hit);
            c.cx = r.cx;
            c.cy = r.cy;
            ++hits;
            any = true;
        }
        if (Collision2D::circleIntersectsAabb(c, brickB)) {
            const auto r = Collision2D::resolveCircleAabb(c, brickB, {40.f, 10.f}, 0.02f);
            CHECK(r.hit);
            c.cx = r.cx;
            c.cy = r.cy;
            ++hits;
            any = true;
        }
        if (!any) {
            break;
        }
    }
    CHECK_EQ(hits, 2);
    CHECK(!Collision2D::circleIntersectsAabb(c, brickA));
    CHECK(!Collision2D::circleIntersectsAabb(c, brickB));
}

TEST_CASE(wall_clamp_left_and_top) {
    const auto w = Collision2D::clampBallCenterToWallsLeftRightTop(
        5.f, 5.f, 14.f, 800.f, 10.f, 10.f);
    CHECK(w.hitLeft);
    CHECK(w.hitTop);
    CHECK_EQ(w.cx, 10.f + 14.f);
    CHECK_EQ(w.cy, 10.f + 14.f);
}

TEST_CASE(wall_clamp_right) {
    const auto w = Collision2D::clampBallCenterToWallsLeftRightTop(
        900.f, 400.f, 14.f, 800.f, 10.f, 10.f);
    CHECK(w.hitRight);
    CHECK(!w.hitLeft);
    CHECK_EQ(w.cx, 800.f - 10.f - 14.f);
}

TEST_CASE(aabb_from_center_size_matches_sfml_semantics) {
    const auto b = Collision2D::aabbFromCenterSize(400.f, 790.f, 150.f, 20.f);
    CHECK_EQ(b.minX, 325.f);
    CHECK_EQ(b.maxX, 475.f);
    CHECK_EQ(b.minY, 780.f);
    CHECK_EQ(b.maxY, 800.f);
}
