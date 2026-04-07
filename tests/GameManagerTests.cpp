#include "TestHarness.h"

#include "../src/GameManager.h"

TEST_CASE(game_manager_starts_with_three_lives) {
    GameManager manager;
    CHECK_EQ(manager.getLives(), 3);
}

TEST_CASE(game_manager_reset_restores_three_lives) {
    GameManager manager;
    manager.loseLife();
    manager.loseLife();
    manager.resetLives();
    CHECK_EQ(manager.getLives(), 3);
}

TEST_CASE(game_manager_lose_life_decrements_until_zero) {
    GameManager manager;
    manager.loseLife();
    manager.loseLife();
    manager.loseLife();
    manager.loseLife();
    CHECK_EQ(manager.getLives(), 0);
}

TEST_CASE(game_manager_have_died_only_after_lives_are_exhausted) {
    GameManager manager;
    CHECK(!manager.haveDied());
    manager.loseLife();
    manager.loseLife();
    manager.loseLife();
    CHECK(manager.haveDied());
}

TEST_CASE(game_manager_state_changes_are_persisted) {
    GameManager manager;
    manager.setGameState(eGame_Play);
    CHECK_EQ(manager.getGameState(), eGame_Play);
}
