# Phase 1 Manual Test Checklist and Execution Record

## Test Run Metadata

- Project: Breakout Game in C++
- Phase: Phase I Source Code Submission
- Branch: `main`
- Reviewed commit: `d94ddaea89df618d48b0169f3c9101fe114c9a2d`
- Build target: `main.exe`
- Platform: Windows + GCC + SFML 3.0.2
- Test date: `2026-04-07`
- Tester: `Steve Dickinson`

## Build Verification

- Build command: `.\scripts\build-phase1.ps1`
- Result: `Pass`
- Notes: The shared toolchain resolver successfully detected the local compiler and SFML install and produced `main.exe` at the repository root.

## Manual Execution Results

All Phase I manual checklist items were executed during this test run and recorded below.

### Paddle Movement Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| PM-01 | Move left with Arrow key | Launch game, hold `Left Arrow` | Paddle moves left until left boundary and does not exit play area | Pass | |
| PM-02 | Move right with Arrow key | Launch game, hold `Right Arrow` | Paddle moves right until right boundary and does not exit play area | Pass | |
| PM-03 | Alternate movement keys | Press `A` and `D` separately | Paddle responds identically to arrow keys | Pass | |

### Ball Collision Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| BC-01 | Wall collision | Allow ball to contact left/right walls | Ball reverses horizontal direction on impact | Pass | |
| BC-02 | Ceiling collision | Allow ball to hit top wall | Ball reverses vertical direction on impact | Pass | |
| BC-03 | Paddle collision | Position paddle under falling ball | Ball reverses vertical direction and remains in play | Pass | |

### Brick Destruction Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| BD-01 | Brick hit detection | Start game and hit a visible brick | Collision is detected and a single brick is affected | Pass | |
| BD-02 | Brick deactivation | Hit the same area where a brick existed | Previously hit brick stays removed (inactive) | Pass | |
| BD-03 | Bounce response | Hit multiple bricks from different angles | Ball bounces after each valid active-brick collision | Pass | |

### Score and Lives Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| SL-01 | Score increments on hit | Hit one brick | Score increases by fixed amount | Pass | |
| SL-02 | Life decrement on miss | Let ball fall below paddle | Lives decreases by 1 and ball resets | Pass | |
| SL-03 | Lives lower bound | Continue missing until 0 lives | Lives never display below 0 | Pass | |

### Win/Loss State Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| WL-01 | Win condition | Clear all active bricks | Game enters win state and displays win text | Pass | |
| WL-02 | Game over condition | Lose all lives | Game enters game-over state and displays game-over text | Pass | |
| WL-03 | Terminal pause | Reach win or game over, try to move paddle | Active gameplay is paused in terminal state | Pass | |

### Restart Flow Tests

| ID | Scenario | Steps | Expected Result | Result | Notes |
| --- | --- | --- | --- | --- | --- |
| RS-01 | Restart from win | Reach win state, press `R` | Game resets score, lives, bricks, paddle, and ball | Pass | |
| RS-02 | Restart from game over | Reach game-over state, press `R` | Game resets to initial playable state | Pass | |
| RS-03 | Ignore restart during play | Press `R` while game is active | No restart occurs during active play | Pass | |

## Defects / Notes

- No defects were observed during this manual test run.

## Submission Notes

- This file serves as both the manual test checklist and the recorded manual execution artifact for the Phase I source code report.
- If screenshots are required, add their filenames or storage location here after the test run is completed.
