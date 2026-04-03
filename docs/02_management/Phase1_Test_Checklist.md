# Phase 1 Manual Test Checklist

## Test Environment

- Build target: `main.exe`
- Platform: Windows + MinGW + SFML 3.0.2
- Test date: ____________________
- Tester: ____________________

## Paddle Movement Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| PM-01 | Move left with Arrow key | Launch game, hold `Left Arrow` | Paddle moves left until left boundary and does not exit play area | [ ] |
| PM-02 | Move right with Arrow key | Launch game, hold `Right Arrow` | Paddle moves right until right boundary and does not exit play area | [ ] |
| PM-03 | Alternate movement keys | Press `A` and `D` separately | Paddle responds identically to arrow keys | [ ] |

## Ball Collision Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| BC-01 | Wall collision | Allow ball to contact left/right walls | Ball reverses horizontal direction on impact | [ ] |
| BC-02 | Ceiling collision | Allow ball to hit top wall | Ball reverses vertical direction on impact | [ ] |
| BC-03 | Paddle collision | Position paddle under falling ball | Ball reverses vertical direction and remains in play | [ ] |

## Brick Destruction Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| BD-01 | Brick hit detection | Start game and hit a visible brick | Collision is detected and a single brick is affected | [ ] |
| BD-02 | Brick deactivation | Hit the same area where a brick existed | Previously hit brick stays removed (inactive) | [ ] |
| BD-03 | Bounce response | Hit multiple bricks from different angles | Ball bounces after each valid active-brick collision | [ ] |

## Score and Lives Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| SL-01 | Score increments on hit | Hit one brick | Score increases by fixed amount | [ ] |
| SL-02 | Life decrement on miss | Let ball fall below paddle | Lives decreases by 1 and ball resets | [ ] |
| SL-03 | Lives lower bound | Continue missing until 0 lives | Lives never display below 0 | [ ] |

## Win/Loss State Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| WL-01 | Win condition | Clear all active bricks | Game enters win state and displays win text | [ ] |
| WL-02 | Game over condition | Lose all lives | Game enters game-over state and displays game-over text | [ ] |
| WL-03 | Terminal pause | Reach win or game over, try to move paddle | Active gameplay is paused in terminal state | [ ] |

## Restart Flow Tests

| ID | Scenario | Steps | Expected Result | Pass/Fail |
| --- | --- | --- | --- | --- |
| RS-01 | Restart from win | Reach win state, press `R` | Game resets score, lives, bricks, paddle, and ball | [ ] |
| RS-02 | Restart from game over | Reach game-over state, press `R` | Game resets to initial playable state | [ ] |
| RS-03 | Ignore restart during play | Press `R` while game is active | No restart occurs during active play | [ ] |

## Notes / Defects

- ____________________________________________
- ____________________________________________
- ____________________________________________
