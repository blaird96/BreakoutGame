#include "Game.h"

#include <algorithm>
#include <array>
#include <cstdint>

#include "GameConstants.h"

Game::Game()
    : window(sf::VideoMode({GameConstants::WindowWidth, GameConstants::WindowHeight}),
             GameConstants::WindowTitle) {
    initialize();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear(sf::Color(0, 0, 0));
        handleInput();
        update();
        render();
        window.display();
    }
}

void Game::initialize() {
    paddle.setSize({GameConstants::PaddleWidth, GameConstants::PaddleHeight});
    paddle.setOrigin({GameConstants::PaddleHalfWidth, GameConstants::PaddleHalfHeight});
    paddle.setPosition({GameConstants::PaddleStartX, GameConstants::PaddleYPos});

    ball.setRadius(GameConstants::BallRadius);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({GameConstants::BallStartX, GameConstants::BallStartY});

    physicsManager.setVelocity(
        {GameConstants::BallInitialVelocityX, GameConstants::BallInitialVelocityY});

    initializeBricks();
}

void Game::initializeBricks() {
    bricks.clear();
    bricks.reserve(GameConstants::BrickRows * GameConstants::BrickColumns);

    const float totalWidth = (GameConstants::BrickColumns * GameConstants::BrickWidth) +
                             ((GameConstants::BrickColumns - 1) * GameConstants::BrickSpacing);
    const float startX = (static_cast<float>(window.getSize().x) - totalWidth) / 2.f;

    for (int row = 0; row < GameConstants::BrickRows; ++row) {
        for (int col = 0; col < GameConstants::BrickColumns; ++col) {
            Brick brick;
            brick.shape.setSize({GameConstants::BrickWidth, GameConstants::BrickHeight});
            brick.shape.setPosition(
                {startX + (col * (GameConstants::BrickWidth + GameConstants::BrickSpacing)),
                 GameConstants::BrickTopOffset +
                     (row * (GameConstants::BrickHeight + GameConstants::BrickSpacing))});
            brick.shape.setFillColor(sf::Color(0, static_cast<std::uint8_t>(145 + (row * 20)), 255));
            brick.isActive = true;
            bricks.push_back(brick);
        }
    }
}

void Game::resetBricks() {
    for (Brick& brick : bricks) {
        brick.isActive = true;
    }
    hasWon = false;
}

void Game::handleEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::handleInput() {
    const float leftBound = GameConstants::BorderXOffset + (paddle.getSize().x / 2.f);
    const float rightBound =
        static_cast<float>(window.getSize().x) - (GameConstants::BorderXOffset + (paddle.getSize().x / 2.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        paddle.setPosition(
            {(paddle.getPosition().x - GameConstants::PaddleSpeed > leftBound
                  ? paddle.getPosition().x - GameConstants::PaddleSpeed
                  : leftBound),
             GameConstants::PaddleYPos});
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        paddle.setPosition(
            {(paddle.getPosition().x + GameConstants::PaddleSpeed < rightBound
                  ? paddle.getPosition().x + GameConstants::PaddleSpeed
                  : rightBound),
             GameConstants::PaddleYPos});
    }
}

void Game::update() {
    collidingBrickIndex.reset();
    ball.setPosition(ball.getPosition() + physicsManager.getVelocity());

    if (ball.getPosition().x >=
            (static_cast<float>(window.getSize().x) - (GameConstants::BorderXOffset + ball.getRadius())) ||
        ball.getPosition().x <= (GameConstants::BorderXOffset + ball.getRadius())) {
        physicsManager.reflectX();
    }

    if (ball.getPosition().y <= (GameConstants::BorderYOffset + ball.getRadius())) {
        physicsManager.reflectY();
    }

    if (ball.getPosition().y >= (GameConstants::PaddleYPos - paddle.getSize().y) &&
        ((ball.getPosition().x > (paddle.getPosition().x - (paddle.getSize().x / 2.f))) &&
         (ball.getPosition().x < (paddle.getPosition().x + (paddle.getSize().x / 2.f))))) {
        physicsManager.reflectY();
    }

    handleBrickCollision();
    hasWon = std::none_of(bricks.begin(), bricks.end(), [](const Brick& brick) { return brick.isActive; });

    if (ball.getPosition().y > GameConstants::KillY) {
        gameManager.loseLife();
        resetBall();
    }

    if (gameManager.haveDied()) {
        paddle.setFillColor(sf::Color::Red);
    }
}

void Game::resetBall() {
    ball.setPosition({GameConstants::BallStartX, GameConstants::BallStartY});
    physicsManager.setVelocity({GameConstants::BallInitialVelocityX, GameConstants::BallInitialVelocityY});
}

void Game::render() {
    drawBorders();
    renderBricks();
    window.draw(paddle);
    window.draw(ball);
}

void Game::renderBricks() {
    for (const Brick& brick : bricks) {
        if (brick.isActive) {
            window.draw(brick.shape);
        }
    }
}

bool Game::ballIntersectsBrick(const Brick& brick) const {
    return ball.getGlobalBounds().findIntersection(brick.shape.getGlobalBounds()).has_value();
}

void Game::handleBrickCollision() {
    for (std::size_t index = 0; index < bricks.size(); ++index) {
        const Brick& brick = bricks[index];
        if (!brick.isActive) {
            continue;
        }
        if (ballIntersectsBrick(brick)) {
            collidingBrickIndex = index;
            break;
        }
    }

    if (collidingBrickIndex.has_value()) {
        bricks[*collidingBrickIndex].isActive = false;
        score += 100;
        physicsManager.reflectY();
        ball.setPosition(ball.getPosition() + physicsManager.getVelocity());
    }
}

void Game::drawBorders() {
    std::array leftLine = {
        sf::Vertex{sf::Vector2f(GameConstants::BorderXOffset, GameConstants::BorderYOffset)},
        sf::Vertex{sf::Vector2f(GameConstants::BorderXOffset,
                                static_cast<float>(window.getSize().y) - GameConstants::BorderYOffset)}};
    window.draw(leftLine.data(), leftLine.size(), sf::PrimitiveType::Lines);

    std::array topLine = {
        sf::Vertex{sf::Vector2f(GameConstants::BorderXOffset, GameConstants::BorderYOffset)},
        sf::Vertex{sf::Vector2f(static_cast<float>(window.getSize().x) - GameConstants::BorderXOffset,
                                GameConstants::BorderYOffset)}};
    window.draw(topLine.data(), topLine.size(), sf::PrimitiveType::Lines);

    std::array rightLine = {
        sf::Vertex{sf::Vector2f(static_cast<float>(window.getSize().x) - GameConstants::BorderXOffset,
                                GameConstants::BorderYOffset)},
        sf::Vertex{sf::Vector2f(static_cast<float>(window.getSize().x) - GameConstants::BorderXOffset,
                                static_cast<float>(window.getSize().y) - GameConstants::BorderYOffset)}};
    window.draw(rightLine.data(), rightLine.size(), sf::PrimitiveType::Lines);
}
