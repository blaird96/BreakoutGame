#pragma once

namespace GameConstants {
constexpr unsigned int WindowWidth = 800;
constexpr unsigned int WindowHeight = 850;
constexpr const char* WindowTitle = "Breakout Game";

constexpr float BorderXOffset = 10.f;
constexpr float BorderYOffset = 10.f;

constexpr float PaddleWidth = 150.f;
constexpr float PaddleHeight = 20.f;
constexpr float PaddleHalfWidth = PaddleWidth / 2.f;
constexpr float PaddleHalfHeight = PaddleHeight / 2.f;
constexpr float PaddleStartX = 400.f;
constexpr float PaddleYPos = 790.f;
constexpr float PaddleSpeed = 0.1f;

constexpr float BallRadius = 14.f;
constexpr float BallStartX = 400.f;
constexpr float BallStartY = 766.f;
constexpr float BallInitialVelocityX = 0.1f;
constexpr float BallInitialVelocityY = -0.1f;

constexpr float KillY = 805.f;
}  // namespace GameConstants
