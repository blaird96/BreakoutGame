class GameManager{
    private:
        int lives;
    public:
        GameManager(){lives = 3;} //amount of lives to start
        int getLives() {return lives;}
        void loseLife() {lives--;}
        bool haveDied() {return lives <= 0;}
};