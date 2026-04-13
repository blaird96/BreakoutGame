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
// Pixels per second (movement uses delta time; stable across frame rates).
constexpr float PaddleSpeedPxPerSec = 420.f;

constexpr float BallRadius = 14.f;
constexpr float BallStartX = 400.f;
constexpr float BallStartY = 766.f;
// Ball travel speed magnitude (px/s); direction set at launch (diagonal + jitter) and on paddle hits.
constexpr float BallSpeedPxPerSec = 340.f;
// Serve: small random angle (deg) and speed variation so each rally feels a bit different.
constexpr float BallServeAngleJitterDeg = 6.f;
constexpr float BallServeSpeedJitter = 0.12f;
// Where the ball strikes the paddle (edge vs center) steers the bounce up to this angle from vertical.
constexpr float PaddleEnglishMaxAngleDeg = 68.f;

constexpr float KillY = 805.f;

constexpr int BrickRows = 5;
constexpr int BrickColumns = 8;
constexpr float BrickWidth = 88.f;
constexpr float BrickHeight = 28.f;
constexpr float BrickSpacing = 8.f;
constexpr float BrickTopOffset = 80.f;

constexpr float MinSpeedMultiplier = 0.35f;
constexpr float MaxSpeedMultiplier = 4.0f;
constexpr float SpeedMultiplierStep = 0.1f;

constexpr float volumeStep = 5.f; 
}  // namespace GameConstants
