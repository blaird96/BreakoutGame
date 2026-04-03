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
    struct Brick {
        sf::RectangleShape shape;
        bool isActive = true;
    };

    void initialize();
    void initializeBricks();
    void resetBricks();
    void handleEvents();
    void handleInput();
    void update();
    void render();
    void renderBricks();
    bool ballIntersectsBrick(const Brick& brick) const;
    void handleBrickCollision();
    void drawBorders();

    sf::RenderWindow window;
    sf::RectangleShape paddle;
    sf::CircleShape ball;
    std::vector<Brick> bricks;
    std::optional<std::size_t> collidingBrickIndex;
    PhysicsManager physicsManager;
    GameManager gameManager;
};
