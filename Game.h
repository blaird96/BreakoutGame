#pragma once

#include <cstddef>
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "GameManager.h"
#include "physicsManager.h"

class Game {
public:
    Game();
    void run();

private:
    enum class GameState {
        Playing,
        Won,
        GameOver
    };

    struct Brick {
        sf::RectangleShape shape;
        bool isActive = true;
    };

    void initialize();
    void initializeBricks();
    void resetBricks();
    void resetGame();
    void handleEvents();
    void handleInput();
    void update();
    void resetBall();
    void render();
    void renderBricks();
    void updateHudText();
    bool ballIntersectsBrick(const Brick& brick) const;
    void handleBrickCollision();
    void drawBorders();

    sf::RenderWindow window;
    sf::RectangleShape paddle;
    sf::CircleShape ball;
    sf::Font hudFont;
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> livesText;
    std::optional<sf::Text> statusText;
    bool hasHudFont = false;
    std::vector<Brick> bricks;
    int score = 0;
    GameState gameState = GameState::Playing;
    std::optional<std::size_t> collidingBrickIndex;
    PhysicsManager physicsManager;
    GameManager gameManager;
};
