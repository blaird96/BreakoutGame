#include "Game.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

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

    if (hudFont.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
        hasHudFont = true;
        scoreText.setFont(hudFont);
        livesText.setFont(hudFont);
        statusText.setFont(hudFont);
        scoreText.setCharacterSize(20);
        livesText.setCharacterSize(20);
        statusText.setCharacterSize(32);
        scoreText.setFillColor(sf::Color::White);
        livesText.setFillColor(sf::Color::White);
        statusText.setFillColor(sf::Color::White);
    } else {
        hasHudFont = false;
    }
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
    gameState = GameState::Playing;
}

void Game::resetGame() {
}

void Game::handleEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::handleInput() {
    if (gameState != GameState::Playing) {
        return;
    }

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
    if (gameState != GameState::Playing) {
        return;
    }

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
    if (std::none_of(bricks.begin(), bricks.end(), [](const Brick& brick) { return brick.isActive; })) {
        gameState = GameState::Won;
        return;
    }

    if (ball.getPosition().y > GameConstants::KillY) {
        gameManager.loseLife();
        resetBall();
    }

    if (gameManager.haveDied()) {
        gameState = GameState::GameOver;
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
    updateHudText();

    if (hasHudFont) {
        window.draw(scoreText);
        window.draw(livesText);
        if (gameState != GameState::Playing) {
            window.draw(statusText);
        }
    }
}

void Game::renderBricks() {
    for (const Brick& brick : bricks) {
        if (brick.isActive) {
            window.draw(brick.shape);
        }
    }
}

void Game::updateHudText() {
    if (!hasHudFont) {
        return;
    }

    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(gameManager.getLives()));
    scoreText.setPosition({GameConstants::BorderXOffset + 10.f, GameConstants::WindowHeight - 40.f});
    livesText.setPosition({GameConstants::WindowWidth - 170.f, GameConstants::WindowHeight - 40.f});

    if (gameState == GameState::Won) {
        statusText.setString("YOU WIN!");
        statusText.setPosition({220.f, 420.f});
    } else if (gameState == GameState::GameOver) {
        statusText.setString("GAME OVER");
        statusText.setPosition({170.f, 420.f});
    } else {
        statusText.setString("");
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
