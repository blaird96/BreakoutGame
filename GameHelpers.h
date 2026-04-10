#pragma once

#include <algorithm>

namespace GameHelpers {
/**
 * Checks if passed value is within passed range, and returns either passed value 
 * or closest bound if outside bounds
 */
inline float clampPaddlePosition(float proposedX, float leftBound, float rightBound) {
    return std::clamp(proposedX, leftBound, rightBound);
}

/**
 * Reduces lives by one and returns the current lives
 */
inline int decrementLife(int currentLives) {
    return (currentLives > 0) ? currentLives - 1 : 0;
}

/**
 * returns false if no bricks, true if bricks remaining
 */
inline bool hasRemainingBricks(int activeBrickCount) {
    return activeBrickCount > 0;
}
}  // namespace GameHelpers
