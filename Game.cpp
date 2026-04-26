#include "Game.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cmath>
#include <filesystem>
#include <random>
#include <string>
#include <iostream>
#include <stdio.h>

#include "GameConstants.h"
#include "GameHelpers.h"
#include "src/Collision2D.h"

namespace {

bool poptable = false;
/**
 * Attempts to load fonts, returns true if did load one from list, false if didn't/can't 
 */
bool tryLoadHudFont(sf::Font& font) {
    namespace fs = std::filesystem;
    // 1) Retro pixel (add PressStart2P-Regular.ttf under assets/fonts/ — SIL OFL).
    // 2) Windows system fonts (readable HUD).
    const fs::path candidates[] = {
        "assets/fonts/PressStart2P-Regular.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/arial.ttf",
    };
    for (const fs::path& path : candidates) {
        std::error_code ec;
        if (!fs::exists(path, ec)) {
            continue;
        }
        if (font.openFromFile(path)) {
            return true;
        }
    }
    return false;
}


/**
 * Return true if the passed key is down either in key or scan form, false if not
 */
bool keyOrScanDown(sf::Keyboard::Key key, sf::Keyboard::Scan scan) {
    return sf::Keyboard::isKeyPressed(key) || sf::Keyboard::isKeyPressed(scan);
}

/**
 * If enter is pressed via Key or scan or numpad enter return true, else return false
 */
bool enterPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Enter || e.scancode == sf::Keyboard::Scan::Enter ||
           e.scancode == sf::Keyboard::Scan::NumpadEnter;
}

/**
 * If escape is pressed via scan or key, return true, else return false
 */
bool escapePressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Escape || e.scancode == sf::Keyboard::Scan::Escape;
}

/**
 * If backspace was pressed in key or scan, return true, else return false
 */
bool backPressed(const sf::Event::KeyPressed& e) {
    return e.code == sf::Keyboard::Key::Backspace || e.scancode == sf::Keyboard::Scan::Backspace;
}

/**
 * Return a random float in the range lo < value < hi
 */
float randomRange(float lo, float hi) {
    thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<float> dist(lo, hi);
    return dist(gen);
}
}  // namespace

/**
 * Constructor
 * Creates window and calls method to initialize game vars
 */
Game::Game()
    : window(sf::VideoMode({GameConstants::WindowWidth, GameConstants::WindowHeight}),
             GameConstants::WindowTitle) {
    initialize();
    createAndPopulateTable();
    loadHighScores();
}

/**
 * Loads music from provided file, sets volume and starts playing
 */
void Game::loadAndPlayMusic( ) {
    if(!Game::bkgMusic.openFromFile(Game::musicFPath)){
        return;
    }
    bkgMusic.setVolume(Game::musicVolume);
    bkgMusic.setLooping(true);
    bkgMusic.play();
}

/**
 * Loads sfx, fiest checks if have a file for each sfx 
 */
void Game::loadOtherSFX() {
    if(!buttonSoundBuffer.loadFromFile(btnAudioFPath)) { std::cout << "Failed to Load Button Audio" << std::endl; }
    else{
        btnSound.emplace(buttonSoundBuffer);
        btnSound->setVolume(70.f);
        btnSoundLoaded = true;
    }
    if(!(ballBounceFPath == "")){
        if(!bounceSoundBuffer.loadFromFile(ballBounceFPath)) { std::cout << "Failed to Load Bounce Audio" << std::endl; }
        else{
            bounceSound.emplace(bounceSoundBuffer);
            bounceSound->setVolume(70.f);
            bounceSoundLoaded = true;
        }
    }
    else { std::cout << "Haven't Assigned/Found a Bounce Audio File" << std::endl; }
    if(!(brickDestroyFPath == "")){
        if(!brickSoundBuffer.loadFromFile(brickDestroyFPath)) { std::cout << "Failed to Load Break Audio" << std::endl; }
        else{
            brickSound.emplace(brickSoundBuffer);
            brickSound->setVolume(70.f);
            brickSoundLoaded = true;
        }
    }
    else { std::cout << "Haven't Assigned/Found a Break Audio File" << std::endl; }
}


/**
 * Actually sets the volume of the music, called after changed in settings menu
 */
void Game::setMusicVolume(){
    bkgMusic.setVolume(Game::musicVolume);
}

/**
 * Accessor of the music volume member 
 */
float Game::getMusicVolume(){ return Game::musicVolume; }

void Game::loadHighScores(){
    sqlite3* dbConnection;

    int exit = sqlite3_open("./BreakOutScores.db", &dbConnection);
    sqlite3_stmt* stmt;
    const char* sql = "SELECT score FROM scores WHERE level = 1;";
    if (sqlite3_prepare_v2(dbConnection, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int score = sqlite3_column_int(stmt, 0);
            std::cout << "Read Score: " << score << std::endl;
            hiScore = score;
        }
    }
    else {std::cout << "Error getting scores" << std::endl; }

    sqlite3_close(dbConnection);
}

void Game::createAndPopulateTable(){
    sqlite3* db;
    std::string tblStr = "CREATE TABLE IF NOT EXISTS SCORES("
                                "level INTEGER PRIMARY KEY,"  
                                "score INTEGER NOT NULL"
                                ")";
    try {
        int exit = 0;
        exit = sqlite3_open("./BreakOutScores.db", &db);

        char* messRes;
        exit = sqlite3_exec(db, tblStr.c_str(), NULL, 0, &messRes);

        if (exit != SQLITE_OK) {
            std::cerr << "Couldn't Make Table" << std::endl;
            sqlite3_free(messRes);
        }
        else { std::cout << "Table Created" << std::endl; }
        sqlite3_close(db);
    }
    catch (const std::exception &e){
        std::cerr << e.what();
    }   

    bool popTable = true;
    int err = sqlite3_open_v2("./BreakOutScores.db", &db, SQLITE_OPEN_READWRITE, NULL);
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM scores;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            popTable = false;
            break;
        }
    }
    sqlite3_finalize(stmt);
    if(popTable){
        char* popErr;
        std::string tblPop = "INSERT INTO scores VALUES (1, 0)";
        int exit = sqlite3_exec(db, tblPop.c_str(), NULL, 0, &popErr);
        if(exit != SQLITE_OK ){
            std::cerr << "Table Population Failed" << std::endl;
            sqlite3_free(popErr);
        }
        else {
            std::cout << "Table Populated with no errors" << std::endl;
        }
    }
    else {std::cout << "Table was already Populated" << std::endl; }

    sqlite3_close(db);
    
    
}



/**
 * Handle gameplay loop monitoring keypresses, mouse clicks and other inputs, clearing the window, and updating/drawing the game elements
 */
void Game::run() {
    while (window.isOpen()) {
        float dt = frameClock_.restart().asSeconds();
        dt = std::clamp(dt, 1.f / 400.f, 0.05f);
        handleEvents();
        pollKeyboardShortcuts();
        handleMouseEvent();
        window.clear(sf::Color(0, 0, 0));
        handleInput(dt);
        update(dt);
        render(); 
        window.display();
    }
}

/**
 * Sets up the fonts, inital ball/paddle position, and blocks
 */
void Game::initialize() {
    window.setKeyRepeatEnabled(false);

    paddle.setSize({GameConstants::PaddleWidth, GameConstants::PaddleHeight});
    paddle.setOrigin({GameConstants::PaddleHalfWidth, GameConstants::PaddleHalfHeight});
    paddle.setPosition({GameConstants::PaddleStartX, GameConstants::PaddleYPos});

    ball.setRadius(GameConstants::BallRadius);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({GameConstants::BallStartX, GameConstants::BallStartY});

    applyBallLaunchVelocity();

    initializeBricks();

    loadAndPlayMusic();
    loadOtherSFX();

    if (tryLoadHudFont(hudFont)) {
        hasHudFont = true;
        scoreText.emplace(hudFont, "", 20);
        livesText.emplace(hudFont, "", 20);
        statusText.emplace(hudFont, "", 32);
        scoreText->setFillColor(sf::Color::White);
        livesText->setFillColor(sf::Color::White);
        statusText->setFillColor(sf::Color::White);
        menuTitleText.emplace(hudFont, "", 40);
        menuLineText.emplace(hudFont, "", 22);
        hiScoreText.emplace(hudFont, "", 22);
    } else {
        hasHudFont = false;
        scoreText.reset();
        livesText.reset();
        statusText.reset();
        menuTitleText.reset();
        menuLineText.reset();
        screenState = ScreenState::MainMenu;
    }
}

/**
 * Creates the brick grid for the game screen using nested for loops
 */
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

/**
 * Makes all bricks in bricks active/shown
 */
void Game::resetBricks() {
    for (Brick& brick : bricks) {
        brick.isActive = true;
    }
    gameState = GameState::Playing;
}

/**
 * resets score, lives, and ball/brick
 */
void Game::resetGame() {
    score = 0;
    gameManager.resetLives();
    resetBricks();
    resetBall();
    paddle.setPosition({GameConstants::PaddleStartX, GameConstants::PaddleYPos});
    paddle.setFillColor(sf::Color::White);
    gameState = GameState::Paused;
}

/**
 * Handles events for teh program, including key presses and the window closing
 */
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

/**
 * Handles mouse clicks/positions in realtion to buttons
 */
void Game::handleMouseEvent(){
    auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    if(screenState == ScreenState::MainMenu){
        if(playBtn.getGlobalBounds().contains(mousePos)){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if(btnSoundLoaded){btnSound->play();}
                screenState = ScreenState::Game;
                resetGame();
            }
            mainMenuSelection = 0;
        }
        if(settingsBtn.getGlobalBounds().contains(mousePos)){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if(btnSoundLoaded){btnSound->play();}
                screenState = ScreenState::Settings;
                settingsSelection = 0;
            }
            mainMenuSelection = 1;
        }
        if(quitBtn.getGlobalBounds().contains(mousePos)){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if(btnSoundLoaded){btnSound->play();}
                window.close();
            }
            mainMenuSelection = 2;
        }
    }
    else if(screenState == ScreenState::Settings){
        if(settingsRtnBtn.getGlobalBounds().contains(mousePos)){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if(btnSoundLoaded){btnSound->play();}
                screenState = ScreenState::MainMenu;
            }
            settingsSelection = 3;
        }
    }
}

/**
 * Handles shortcuts to leave/reset the game while playing
 */
void Game::pollKeyboardShortcuts() {
    const bool esc = keyOrScanDown(sf::Keyboard::Key::Escape, sf::Keyboard::Scan::Escape);
    const bool m = keyOrScanDown(sf::Keyboard::Key::M, sf::Keyboard::Scan::M);
    const bool r = keyOrScanDown(sf::Keyboard::Key::R, sf::Keyboard::Scan::R);
    const bool sp = keyOrScanDown(sf::Keyboard::Key::Space, sf::Keyboard::Scan::Space);

    if (screenState == ScreenState::Game) {
        if (gameState == GameState::Playing) {
            if (esc && !prevEscDown_) {
                screenState = ScreenState::MainMenu;
            }
        } else {
            if ((esc && !prevEscDown_) || (m && !prevMDown_)) {
                screenState = ScreenState::MainMenu;
            } else if ((r && !prevRDown_) || (sp && !prevSpaceDown_)) {
                resetGame();
            }
        }
    }

    prevEscDown_ = esc;
    prevMDown_ = m;
    prevRDown_ = r;
    prevSpaceDown_ = sp;
}

/**
 * Handles keypresses in the main and settings menu for cycling through options and 'pressing'
 * the buttons with the'enter' keys
 */
void Game::processKeyPressed(const sf::Event::KeyPressed& key) {
    const auto k = key.code;

    if (screenState == ScreenState::MainMenu) {
        if (!hasHudFont) {
            if (k == sf::Keyboard::Key::Num1) {
                screenState = ScreenState::Game;
                resetGame();
            } else if (k == sf::Keyboard::Key::Num2) {
                screenState = ScreenState::Settings;
                settingsSelection = 0;
            } else if (k == sf::Keyboard::Key::Num3) {
                window.close();
            }
            return;
        }
        if (k == sf::Keyboard::Key::Up) {
            mainMenuSelection = (mainMenuSelection + 2) % 3;
        } else if (k == sf::Keyboard::Key::Down) {
            mainMenuSelection = (mainMenuSelection + 1) % 3;
        } else if (enterPressed(key)) {
            if (mainMenuSelection == 0) {
                if(btnSoundLoaded){btnSound->play();}
                screenState = ScreenState::Game;
                resetGame();
            } else if (mainMenuSelection == 1) {
                if(btnSoundLoaded){btnSound->play();}
                screenState = ScreenState::Settings;
                settingsSelection = 0;
            } else {
                if(btnSoundLoaded){btnSound->play();}
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
            settingsSelection = (settingsSelection + 3) % 4;
        } else if (k == sf::Keyboard::Key::Down) {
            settingsSelection = (settingsSelection + 1) % 4;
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
            } else if (settingsSelection == 2){
                musicVolume = std::clamp(
                    musicVolume - GameConstants::volumeStep,
                    0.f, 
                    100.f
                );
                setMusicVolume();
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
            } else if (settingsSelection == 2){
                musicVolume = std::clamp(
                    musicVolume + GameConstants::volumeStep,
                    0.f, 
                    100.f
                );
                setMusicVolume();
            }
        } else if (enterPressed(key) && settingsSelection == 3) {
            if(btnSoundLoaded){btnSound->play();}
            screenState = ScreenState::MainMenu;
        }
        return;
    }
}

/**
 * Sets the ball velocity for the start of the program and converts it back to a vector 2 for future 
 * use in the program.
 */
void Game::applyBallLaunchVelocity() {
    const float baseSpeed = GameConstants::BallSpeedPxPerSec * ballSpeedMultiplier;
    const float speedJitter =
        1.f + randomRange(-GameConstants::BallServeSpeedJitter, GameConstants::BallServeSpeedJitter);
    const float speed = baseSpeed * speedJitter;
    const float angleJitterDeg =
        randomRange(-GameConstants::BallServeAngleJitterDeg, GameConstants::BallServeAngleJitterDeg);
    const float angleDeg = -45.f + angleJitterDeg;
    const float rad = angleDeg * (3.14159265f / 180.f);
    physicsManager.setVelocity({speed * std::cos(rad), speed * std::sin(rad)});
}

/**
 * handles the gameplay related keypresses including moving the paddle and unpausing the game when paused. 
 */
void Game::handleInput(float dt) {
    if (screenState != ScreenState::Game || gameState != GameState::Playing) {
        if(gameState == GameState::Paused && (
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||  
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
        )){
            gameState = GameState::Playing;
        }
        else{ return; }
    }

    const float paddleStep = GameConstants::PaddleSpeedPxPerSec * paddleSpeedMultiplier * dt;
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

/**
 * Handles the ball collisions including the paddle, walls, and the bricks
 */
void Game::update(float dt) {
    (void)dt;
    if (screenState != ScreenState::Game || gameState != GameState::Playing) {
        return;
    }

    collidingBrickIndex.reset();
    const float winW = static_cast<float>(window.getSize().x);
    const float ballR = ball.getRadius();

    ball.setPosition(ball.getPosition() + physicsManager.getVelocity() * dt);
    sf::Vector2f pos = ball.getPosition();

    const float minX = GameConstants::BorderXOffset + ballR;
    const float maxX = winW - GameConstants::BorderXOffset - ballR;
    const float minY = GameConstants::BorderYOffset + ballR;
    bool wallBounceSound = false;
    if (pos.x < minX) {
        pos.x = minX;
        physicsManager.reflectX();
        wallBounceSound = true;
    } else if (pos.x > maxX) {
        pos.x = maxX;
        physicsManager.reflectX();
        wallBounceSound = true;
    }
    if (pos.y < minY) {
        pos.y = minY;
        physicsManager.reflectY();
        wallBounceSound = true;
    }
    if (wallBounceSound && bounceSoundLoaded) {
        bounceSound->play();
    }
    ball.setPosition(pos);

    handleBrickCollisions();

    pos = ball.getPosition();
    sf::Vector2f vel = physicsManager.getVelocity();
    if (vel.y > 0.f) {
        const Collision2D::Circle ballCirc{pos.x, pos.y, ballR};
        const sf::Vector2f paddlePos = paddle.getPosition();
        const Collision2D::Aabb paddleAabb = Collision2D::aabbFromCenterSize(
            paddlePos.x, paddlePos.y, paddle.getSize().x, paddle.getSize().y);
        if (Collision2D::circleIntersectsAabb(ballCirc, paddleAabb)) {
            const auto sep = Collision2D::resolveCircleAabb(
                ballCirc, paddleAabb, {vel.x, vel.y}, 0.02f);
            ball.setPosition({sep.cx, sep.cy});
            if (bounceSoundLoaded) {
                bounceSound->play();
            }
            vel = physicsManager.getVelocity();
            float speed = std::hypot(vel.x, vel.y);
            const float minSpeed = GameConstants::BallSpeedPxPerSec * ballSpeedMultiplier * 0.5f;
            if (speed < minSpeed) {
                speed = GameConstants::BallSpeedPxPerSec * ballSpeedMultiplier;
            }
            const float halfW = paddle.getSize().x * 0.5f;
            const float hitT =
                std::clamp((ball.getPosition().x - paddlePos.x) / halfW, -1.f, 1.f);
            const float maxRad = GameConstants::PaddleEnglishMaxAngleDeg * (3.14159265f / 180.f);
            const float angle = hitT * maxRad;
            const float newVx = std::sin(angle) * speed;
            const float newVy = -std::cos(angle) * speed;
            physicsManager.setVelocity({newVx, newVy});
        }
    }
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
        //paddle.setFillColor(sf::Color::Red);
    }
}

/**
 * Sets the ball to its constant start position and applies a launch velocity
 */
void Game::resetBall() {
    ball.setPosition({GameConstants::BallStartX, GameConstants::BallStartY});
    gameState = GameState::Paused;
    applyBallLaunchVelocity();
}

/**
 * Renders the various elements beased on the Screen state, including the bricks, border, paddle
 * and ball if in play mode.
 */
void Game::render() {
    if (screenState == ScreenState::MainMenu) {
        renderMainMenu();
        return;
    }
    if (screenState == ScreenState::Settings) {
        renderSettingsScreen();
        return;
    }

    window.setTitle(GameConstants::WindowTitle);

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

/**
 * Renders the main menu and the menu options, with error handling if fonts didn'y load
 */
void Game::renderMainMenu() {
    if (!hasHudFont) {
        window.setTitle(
            "Breakout | Keys: 1 Play  2 Settings  3 Quit  |  Or click colored bars (no font loaded)");
        const float cx = static_cast<float>(window.getSize().x) / 2.f;
        auto layout = [&](sf::RectangleShape& btn, float y, const sf::Color& fill) {
            btn.setSize({260.f, 48.f});
            btn.setOrigin({130.f, 24.f});
            btn.setPosition({cx, y});
            btn.setFillColor(fill);
            btn.setOutlineThickness(2.f);
            btn.setOutlineColor(sf::Color::White);
            window.draw(btn);
        };
        layout(playBtn, 320.f, sf::Color(30, 100, 40));
        layout(settingsBtn, 400.f, sf::Color(40, 60, 120));
        layout(quitBtn, 480.f, sf::Color(120, 30, 30));
        return;
    }

    window.setTitle(GameConstants::WindowTitle);

    if (!menuTitleText || !menuLineText) {
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
        if(i == 0){
            playBtn.setSize({b.size.x + 20, b.size.y + 20});
            playBtn.setOrigin({(b.size.x + 20.f) / 2.f, (b.size.y + 20.f) / 2.f});
            playBtn.setPosition({cx, 340.f + (i * 50.f)});
            playBtn.setFillColor(sf::Color::Transparent);
            playBtn.setOutlineThickness(3.f);
            playBtn.setOutlineColor(i == mainMenuSelection ? sf::Color::Yellow : sf::Color::Transparent);
            window.draw(playBtn);
        }
        else if(i == 1){
            settingsBtn.setSize({b.size.x + 20, b.size.y + 20});
            settingsBtn.setOrigin({(b.size.x + 20.f) / 2.f, (b.size.y + 20.f) / 2.f});
            settingsBtn.setPosition({cx, 340.f + (i * 50.f)});
            settingsBtn.setFillColor(sf::Color::Transparent);
            settingsBtn.setOutlineThickness(3.f);
            settingsBtn.setOutlineColor(i == mainMenuSelection ? sf::Color::Yellow : sf::Color::Transparent);
            window.draw(settingsBtn);
        }
        else if(i == 2){
            quitBtn.setSize({b.size.x + 20, b.size.y + 20});
            quitBtn.setOrigin({(b.size.x + 20.f) / 2.f, (b.size.y + 20.f) / 2.f});
            quitBtn.setPosition({cx, 340.f + (i * 50.f)});
            quitBtn.setFillColor(sf::Color::Transparent);
            quitBtn.setOutlineThickness(3.f);
            quitBtn.setOutlineColor(i == mainMenuSelection ? sf::Color::Yellow : sf::Color::Transparent);
            window.draw(quitBtn);
        }
        window.draw(*menuLineText);
    }

    if(hiScore > 0){
        std::string scoreString = "High Score: " + std::to_string(hiScore);
        hiScoreText->setString(scoreString);
        const sf::FloatRect b = hiScoreText->getLocalBounds();
        hiScoreText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        hiScoreText->setPosition({cx, 550.f});
        window.draw(*hiScoreText);
    }
    

    menuLineText->setString("Up/Down: Navigate \n  Enter: Select");
    menuLineText->setFillColor(sf::Color(180, 180, 180));
    {
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuLineText->setPosition({cx, 720.f});
    window.draw(*menuLineText);
}

/**
 * Renders the settings menu with some error handling
 */
void Game::renderSettingsScreen() {
    if (!hasHudFont) {
        window.setTitle("SETTINGS (no font) — Esc: back to menu");
        return;
    }
    if (!menuTitleText || !menuLineText) {
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
    std::string line2 = 
        "Music Volume: " + (static_cast<int>(musicVolume) != 0 ? (std::to_string(static_cast<int>(musicVolume)) + "% ") : "MUTE") + " (Left/Right)";
    const char* line3 = "Back to menu";

    const std::string lines[4] = {line0, line1, line2, line3};
    for (int i = 0; i < 4; ++i) {
        menuLineText->setString(lines[i]);
        menuLineText->setFillColor(i == settingsSelection ? sf::Color::Yellow : sf::Color::White);
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        menuLineText->setPosition({cx, 300.f + (i * 60.f)});
        window.draw(*menuLineText);
        if(i == 3){
            settingsRtnBtn.setSize({b.size.x + 20, b.size.y + 20});
            settingsRtnBtn.setOrigin({(b.size.x + 20.f) / 2.f, (b.size.y + 20.f) / 2.f});
            settingsRtnBtn.setPosition({cx, 300.f + (i * 60.f)});
            settingsRtnBtn.setFillColor(sf::Color::Transparent);
            settingsRtnBtn.setOutlineThickness(3.f);
            settingsRtnBtn.setOutlineColor(i == settingsSelection ? sf::Color::Yellow : sf::Color::Transparent);
            window.draw(settingsRtnBtn);
        }
    }

    menuLineText->setString("   Up/Down: Row  \nLeft/Right: Adjust \n Enter/Esc: Back");
    menuLineText->setFillColor(sf::Color(180, 180, 180));
    {
        const sf::FloatRect b = menuLineText->getLocalBounds();
        menuLineText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    }
    menuLineText->setPosition({cx, 720.f});
    window.draw(*menuLineText);
}

/**
 * For each brick in the brick list, if active render/draw it, else don't
 */
void Game::renderBricks() {
    for (const Brick& brick : bricks) {
        if (brick.isActive) {
            window.draw(brick.shape);
        }
    }
}

/**
 * Updates and displays the current life, score etc. while playing the game
 */
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
        statusText->setString("    GAME OVER\nR / Space: Try Again \n  M / Esc: Menu");
        const sf::FloatRect b = statusText->getLocalBounds();
        statusText->setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        statusText->setPosition({cx, 400.f});
    } else {
        statusText->setCharacterSize(32);
        statusText->setOrigin({0.f, 0.f});
        statusText->setString("");
    }
}

/**
 * Resolves ball–brick overlaps: side-aware reflection, separation, and multiple hits per frame
 * (bounded) so the ball cannot tunnel through stacked bricks.
 */
void Game::handleBrickCollisions() {
    constexpr int kMaxResolveIters = 8;
    constexpr float kSepEpsilon = 0.02f;
    bool playedBrickSound = false;

    for (int iter = 0; iter < kMaxResolveIters; ++iter) {
        const Collision2D::Circle ballCirc{
            ball.getPosition().x, ball.getPosition().y, ball.getRadius()};
        std::optional<std::size_t> hitIndex;

        for (std::size_t i = 0; i < bricks.size(); ++i) {
            if (!bricks[i].isActive) {
                continue;
            }
            const sf::FloatRect gr = bricks[i].shape.getGlobalBounds();
            const Collision2D::Aabb box{gr.position.x,
                                        gr.position.y,
                                        gr.position.x + gr.size.x,
                                        gr.position.y + gr.size.y};
            if (Collision2D::circleIntersectsAabb(ballCirc, box)) {
                hitIndex = i;
                break;
            }
        }

        if (!hitIndex.has_value()) {
            break;
        }

        const sf::FloatRect gr = bricks[*hitIndex].shape.getGlobalBounds();
        const Collision2D::Aabb box{gr.position.x,
                                    gr.position.y,
                                    gr.position.x + gr.size.x,
                                    gr.position.y + gr.size.y};
        const sf::Vector2f v = physicsManager.getVelocity();
        const auto resolved =
            Collision2D::resolveCircleAabb(ballCirc, box, {v.x, v.y}, kSepEpsilon);

        bricks[*hitIndex].isActive = false;
        score += 100;
        collidingBrickIndex = hitIndex;
        playedBrickSound = true;

        if (resolved.reflectX) {
            physicsManager.reflectX();
        } else {
            physicsManager.reflectY();
        }
        ball.setPosition({resolved.cx, resolved.cy});
    }

    if (playedBrickSound && brickSoundLoaded) {
        brickSound->play();
    }
}

/**
 * Creates the border of the play screen
 */
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
