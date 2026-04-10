/*DON'T THINK THIS FILE/CLASS ISN'T NEEDED FOR THE PROGRAM */

#pragma once

#include "../GameHelpers.h"

enum eGame_State {
    eGame_Main,
    eGame_LevelSelect,
    eGame_Play
};

class GameManager{
    private:
        int lives;
        eGame_State gameState;
    public:
        GameManager(); //amount of lives to start
        int getLives() {return lives;}
        void resetLives() { lives = 3; }
        void loseLife() { lives = GameHelpers::decrementLife(lives); }
        bool haveDied() {return lives <= 0;}
        void setGameState(eGame_State state) { gameState = state; }
        eGame_State getGameState() {return gameState;}
};
