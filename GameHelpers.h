#pragma once

#include <algorithm>

namespace GameHelpers {
inline float clampPaddlePosition(float proposedX, float leftBound, float rightBound) {
    return std::clamp(proposedX, leftBound, rightBound);
}

inline int decrementLife(int currentLives) {
    return (currentLives > 0) ? currentLives - 1 : 0;
}

inline bool hasRemainingBricks(int activeBrickCount) {
    return activeBrickCount > 0;
}
}  // namespace GameHelpers
