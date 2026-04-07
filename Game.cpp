#include "Game.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cmath>
#include <string>

#include "GameConstants.h"
#include "GameHelpers.h"

namespace {
bool enterPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Enter || e.scancode == sf::Keyboard::Scan::Enter ||
           e.scancode == sf::Keyboard::Scan::NumpadEnter;
}

bool escapePressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Escape || e.scancode == sf::Keyboard::Scan::Escape;
}

bool rPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::R || e.scancode == sf::Keyboard::Scan::R;
}

bool mPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::M || e.scancode == sf::Keyboard::Scan::M;
}

bool spacePressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Space || e.scancode == sf::Keyboard::Scan::Space;
}

bool backPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Backspace || e.scancode == sf::Keyboard::Scan::Backspace;
}
}  // namespace

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
    window.setKeyRepeatEnabled(false);

    paddle.setSize({GameConstants::PaddleWidth, GameConstants::PaddleHeight});
    paddle.setOrigin({GameConstants::PaddleHalfWidth, GameConstants::PaddleHalfHeight});
    paddle.setPosition({GameConstants::PaddleStartX, GameConstants::PaddleYPos});

    ball.setRadius(GameConstants::BallRadius);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({GameConstants::BallStartX, GameConstants::BallStartY});

    physicsManager.setVelocity({GameConstants::BallInitialVelocityX * ballSpeedMultiplier,
                                GameConstants::BallInitialVelocityY * ballSpeedMultiplier});

    initializeBricks();

    if (hudFont.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
        hasHudFont = true;
        scoreText.emplace(hudFont, "", 20);
        livesText.emplace(hudFont, "", 20);
        statusText.emplace(hudFont, "", 32);
        scoreText->setFillColor(sf::Color::White);
        livesText->setFillColor(sf::Color::White);
        statusText->setFillColor(sf::Color::White);
        menuTitleText.emplace(hudFont, "", 40);
        menuLineText.emplace(hudFont, "", 22);
    } else {
        hasHudFont = false;
        scoreText.reset();
        livesText.reset();
        statusText.reset();
        menuTitleText.reset();
        menuLineText.reset();
        screenState = ScreenState::Game;
        resetGame();
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
    score = 0;
    gameManager.resetLives();
    resetBricks();
    resetBall();
    paddle.setPosition({GameConstants::PaddleStartX, GameConstants::PaddleYPos});
    paddle.setFillColor(sf::Color::White);
    gameState = GameState::Playing;
}

void Game::handleEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            processKeyPressed(*keyPressed);
        }
    }
}

void Game::processKeyPressed(const sf::Event::KeyPressed& key) {
    const auto k = key.code;

    if (screenState == ScreenState::MainMenu) {
        if (k == sf::Keyboard::Key::Up) {
            mainMenuSelection = (mainMenuSelection + 2) % 3;
        } else if (k == sf::Keyboard::Key::Down) {
            mainMenuSelection = (mainMenuSelection + 1) % 3;
        } else if (enterPressed(key)) {
            if (mainMenuSelection == 0) {
                screenState = ScreenState::Game;
                resetGame();
            } else if (mainMenuSelection == 1) {
                screenState = ScreenState::Settings;
                settingsSelection = 0;
            } else {
                window.close();
            }
        }
        return;
    }

    if (screenState == ScreenState::Settings) {
        if (escapePressed(key) || backPressed(key)) {
            screenState = ScreenState::MainMenu;
            return;
        }
        if (k == sf::Keyboard::Key::Up) {
            settingsSelection = (settingsSelection + 2) % 3;
        } else if (k == sf::Keyboard::Key::Down) {
            settingsSelection = (settingsSelection + 1) % 3;
        } else if (k == sf::Keyboard::Key::Left) {
            if (settingsSelection == 0) {
                paddleSpeedMultiplier = std::clamp(
                    paddleSpeedMultiplier - GameConstants::SpeedMultiplierStep,
                    GameConstants::MinSpeedMultiplier,
                    GameConstants::MaxSpeedMultiplier);
            } else if (settingsSelection == 1) {
                ballSpeedMultiplier = std::clamp(
                    ballSpeedMultiplier - GameConstants::SpeedMultiplierStep,
                    GameConstants::MinSpeedMultiplier,
                    GameConstants::MaxSpeedMultiplier);
            }
        } else if (k == sf::Keyboard::Key::Right) {
            if (settingsSelection == 0) {
                paddleSpeedMultiplier = std::clamp(
                    paddleSpeedMultiplier + GameConstants::SpeedMultiplierStep,
                    GameConstants::MinSpeedMultiplier,
                    GameConstants::MaxSpeedMultiplier);
            } else if (settingsSelection == 1) {
                ballSpeedMultiplier = std::clamp(
                    ballSpeedMultiplier + GameConstants::SpeedMultiplierStep,
                    GameConstants::MinSpeedMultiplier,
                    GameConstants::MaxSpeedMultiplier);
            }
        } else if (enterPressed(key) && settingsSelection == 2) {
            screenState = ScreenState::MainMenu;
        }
        return;
    }

    if (screenState == ScreenState::Game) {
        const bool terminal = (gameState == GameState::Won || gameState == GameState::GameOver);
        if (terminal) {
            if (rPressed(key) || spacePressed(key)) {
                resetGame();
            } else if (escapePressed(key) || mPressed(key)) {
                screenState = ScreenState::MainMenu;
            }
        }
    }
}

void Game::handleInput() {
    if (screenState != ScreenState::Game || gameState != GameState::Playing) {
        return;
    }

    const float paddleStep = GameConstants::PaddleSpeed * paddleSpeedMultiplier;
    const float leftBound = GameConstants::BorderXOffset + (paddle.getSize().x / 2.f);
    const float rightBound =
        static_cast<float>(window.getSize().x) - (GameConstants::BorderXOffset + (paddle.getSize().x / 2.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        const float nextX = GameHelpers::clampPaddlePosition(
            paddle.getPosition().x - paddleStep, leftBound, rightBound);
        paddle.setPosition({nextX, GameConstants::PaddleYPos});
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        const float nextX = GameHelpers::clampPaddlePosition(
            paddle.getPosition().x + paddleStep, leftBound, rightBound);
        paddle.setPosition({nextX, GameConstants::PaddleYPos});
    }
}

void Game::update() {
    if (screenState != ScreenState::Game || gameState != GameState::Playing) {
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
    const int activeBrickCount = static_cast<int>(
        std::count_if(bricks.begin(), bricks.end(), [](const Brick& brick) { return brick.isActive; }));
    if (!GameHelpers::hasRemainingBricks(activeBrickCount)) {
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
    physicsManager.setVelocity({GameConstants::BallInitialVelocityX * ballSpeedMultiplier,
                                GameConstants::BallInitialVelocityY * ballSpeedMultiplier});
}

void Game::render() {
    if (screenState == ScreenState::MainMenu) {
        renderMainMenu();
        return;
    }
    if (screenState == ScreenState::Settings) {
        renderSettingsScreen();
        return;
    }

    drawBorders();
    renderBricks();
    window.draw(paddle);
    window.draw(ball);
    updateHudText();

    if (hasHudFont && scoreText && livesText && statusText) {
        window.draw(*scoreText);
        window.draw(*livesText);
        if (gameState != GameState::Playing) {
            window.draw(*statusText);
        }
    }
}

void Game::renderMainMenu() {
    if (!hasHudFont || !menuTitleText || !menuLineText) {
        return;
    }

    const float cx = static_cast<float>(window.getSize().x) / 2.f;
    menuTitleText->setString("BREAKOUT");
    menuTitleText->setFillColor(sf::Color::White);
    {
        const sf::FloatRect b = menuTitleText->getLocalBounds();
        menuTitleText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuTitleText->setPosition({cx, 200.f});
    window.draw(*menuTitleText);

    const char* labels[3] = {"Play", "Settings", "Quit"};
    for (int i = 0; i < 3; ++i) {
        menuLineText->setString(labels[i]);
        menuLineText->setFillColor(i == mainMenuSelection ? sf::Color::Yellow : sf::Color::White);
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        menuLineText->setPosition({cx, 340.f + (i * 50.f)});
        window.draw(*menuLineText);
    }

    menuLineText->setString("Up/Down: navigate   Enter: select");
    menuLineText->setFillColor(sf::Color(180, 180, 180));
    {
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuLineText->setPosition({cx, 720.f});
    window.draw(*menuLineText);
}

void Game::renderSettingsScreen() {
    if (!hasHudFont || !menuTitleText || !menuLineText) {
        return;
    }

    const float cx = static_cast<float>(window.getSize().x) / 2.f;
    menuTitleText->setString("SETTINGS");
    menuTitleText->setFillColor(sf::Color::White);
    {
        const sf::FloatRect b = menuTitleText->getLocalBounds();
        menuTitleText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuTitleText->setPosition({cx, 160.f});
    window.draw(*menuTitleText);

    auto pct = [](float m) {
        return static_cast<int>(std::lround(m * 100.f));
    };

    std::string line0 =
        "Paddle speed: " + std::to_string(pct(paddleSpeedMultiplier)) + "%  (Left/Right)";
    std::string line1 =
        "Ball speed: " + std::to_string(pct(ballSpeedMultiplier)) + "%  (Left/Right)";
    const char* line2 = "Back to menu";

    const std::string lines[3] = {line0, line1, line2};
    for (int i = 0; i < 3; ++i) {
        menuLineText->setString(lines[i]);
        menuLineText->setFillColor(i == settingsSelection ? sf::Color::Yellow : sf::Color::White);
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        menuLineText->setPosition({cx, 300.f + (i * 60.f)});
        window.draw(*menuLineText);
    }

    menuLineText->setString("Up/Down: row   Left/Right: adjust   Enter/Esc: back");
    menuLineText->setFillColor(sf::Color(180, 180, 180));
    {
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuLineText->setPosition({cx, 720.f});
    window.draw(*menuLineText);
}

void Game::renderBricks() {
    for (const Brick& brick : bricks) {
        if (brick.isActive) {
            window.draw(brick.shape);
        }
    }
}

void Game::updateHudText() {
    if (!hasHudFont || !scoreText || !livesText || !statusText) {
        return;
    }

    scoreText->setString("Score: " + std::to_string(score));
    livesText->setString("Lives: " + std::to_string(gameManager.getLives()));
    scoreText->setPosition({GameConstants::BorderXOffset + 10.f, GameConstants::WindowHeight - 40.f});
    livesText->setPosition({GameConstants::WindowWidth - 170.f, GameConstants::WindowHeight - 40.f});

    const float cx = static_cast<float>(window.getSize().x) / 2.f;

    if (gameState == GameState::Won) {
        statusText->setCharacterSize(20);
        statusText->setString("YOU WIN!\nR / Space: play again     M / Esc: menu");
        const sf::FloatRect b = statusText->getLocalBounds();
        statusText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        statusText->setPosition({cx, 400.f});
    } else if (gameState == GameState::GameOver) {
        statusText->setCharacterSize(20);
        statusText->setString("GAME OVER\nR / Space: try again     M / Esc: menu");
        const sf::FloatRect b = statusText->getLocalBounds();
        statusText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        statusText->setPosition({cx, 400.f});
    } else {
        statusText->setCharacterSize(32);
        statusText->setOrigin({0.f, 0.f});
        statusText->setString("");
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
