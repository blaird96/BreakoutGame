#pragma once

namespace GameHelpers {
float clampPaddlePosition(float proposedX, float leftBound, float rightBound);
int decrementLife(int currentLives);
bool hasRemainingBricks(int activeBrickCount);
}  // namespace GameHelpers
