class GameManager{
    private:
        int lives;
    public:
        GameManager(){lives = 3;} //amount of lives to start
        int getLives() {return lives;}
        void resetLives() {lives = 3;}
        void loseLife() {
            if (lives > 0) {
                lives--;
            }
        }
        bool haveDied() {return lives <= 0;}
};