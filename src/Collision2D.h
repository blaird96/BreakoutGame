#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>

namespace Collision2D {

struct Vec2 {
    float x = 0.f;
    float y = 0.f;
};

struct Circle {
    float cx = 0.f;
    float cy = 0.f;
    float r = 0.f;
};

/** Inclusive axis-aligned box: [minX, maxX] x [minY, maxY]. */
struct Aabb {
    float minX = 0.f;
    float minY = 0.f;
    float maxX = 0.f;
    float maxY = 0.f;
};

inline bool circleIntersectsAabb(const Circle& c, const Aabb& b) {
    const float qx = std::clamp(c.cx, b.minX, b.maxX);
    const float qy = std::clamp(c.cy, b.minY, b.maxY);
    const float dx = c.cx - qx;
    const float dy = c.cy - qy;
    return dx * dx + dy * dy <= c.r * c.r;
}

/**
 * If the circle overlaps the AABB, separates the center along the collision normal
 * (closest point on the box to the circle center) and reports whether the dominant
 * contact normal is horizontal (reflect X) or vertical (reflect Y).
 *
 * When the circle center lies exactly on the closest point (e.g. deep inside a thick
 * slab), falls back to comparing penetration along each axis using half extents.
 */
struct CircleAabbResolveResult {
    bool hit = false;
    bool reflectX = false;
    float cx = 0.f;
    float cy = 0.f;
};

inline CircleAabbResolveResult resolveCircleAabb(const Circle& c,
                                                const Aabb& b,
                                                const Vec2& velocity,
                                                float epsilon) {
    CircleAabbResolveResult out;
    out.cx = c.cx;
    out.cy = c.cy;

    if (!circleIntersectsAabb(c, b)) {
        return out;
    }

    const float qx = std::clamp(c.cx, b.minX, b.maxX);
    const float qy = std::clamp(c.cy, b.minY, b.maxY);
    float dx = c.cx - qx;
    float dy = c.cy - qy;
    const float distSq = dx * dx + dy * dy;
    constexpr float kEps = 1e-5f;

    if (distSq > kEps * kEps) {
        const float dist = std::sqrt(distSq);
        dx /= dist;
        dy /= dist;
        const float pen = c.r - dist + epsilon;
        out.cx = c.cx + dx * pen;
        out.cy = c.cy + dy * pen;
        if (std::fabs(dx) >= std::fabs(dy)) {
            out.reflectX = true;
        } else {
            out.reflectX = false;
        }
        // Tie-break near 45°: prefer axis implied by incoming velocity (into the box).
        if (std::fabs(std::fabs(dx) - std::fabs(dy)) < 1e-4f) {
            if (std::fabs(velocity.x) >= std::fabs(velocity.y)) {
                out.reflectX = true;
            } else {
                out.reflectX = false;
            }
        }
    } else {
        // Degenerate closest point (center on/in the box slab): move the circle fully
        // outside through the nearest face.
        const float leftTarget = b.minX - c.r - epsilon;
        const float rightTarget = b.maxX + c.r + epsilon;
        const float topTarget = b.minY - c.r - epsilon;
        const float bottomTarget = b.maxY + c.r + epsilon;

        const float moveLeft = std::fabs(c.cx - leftTarget);
        const float moveRight = std::fabs(rightTarget - c.cx);
        const float moveTop = std::fabs(c.cy - topTarget);
        const float moveBottom = std::fabs(bottomTarget - c.cy);

        float best = moveLeft;
        std::int8_t axis = 0;  // 0=L,1=R,2=T,3=B
        if (moveRight < best) {
            best = moveRight;
            axis = 1;
        }
        if (moveTop < best) {
            best = moveTop;
            axis = 2;
        }
        if (moveBottom < best) {
            axis = 3;
        }

        switch (axis) {
            case 0:
                out.cx = leftTarget;
                out.reflectX = true;
                break;
            case 1:
                out.cx = rightTarget;
                out.reflectX = true;
                break;
            case 2:
                out.cy = topTarget;
                out.reflectX = false;
                break;
            default:
                out.cy = bottomTarget;
                out.reflectX = false;
                break;
        }
    }

    out.hit = true;
    return out;
}

/**
 * Clamps the ball center against left, right, and top playfield borders (radius inset).
 * The bottom is open (death zone handled elsewhere).
 */
struct WallClampResult {
    float cx = 0.f;
    float cy = 0.f;
    bool hitLeft = false;
    bool hitRight = false;
    bool hitTop = false;
};

inline WallClampResult clampBallCenterToWallsLeftRightTop(float cx,
                                                          float cy,
                                                          float radius,
                                                          float winW,
                                                          float borderX,
                                                          float borderY) {
    WallClampResult w;
    const float minX = borderX + radius;
    const float maxX = winW - borderX - radius;
    const float minY = borderY + radius;

    w.cx = cx;
    w.cy = cy;

    if (w.cx < minX) {
        w.cx = minX;
        w.hitLeft = true;
    } else if (w.cx > maxX) {
        w.cx = maxX;
        w.hitRight = true;
    }

    if (w.cy < minY) {
        w.cy = minY;
        w.hitTop = true;
    }

    return w;
}

inline Aabb aabbFromCenterSize(float centerX, float centerY, float width, float height) {
    const float halfW = width * 0.5f;
    const float halfH = height * 0.5f;
    return Aabb{centerX - halfW, centerY - halfH, centerX + halfW, centerY + halfH};
}

}  // namespace Collision2D
