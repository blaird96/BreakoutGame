#pragma once

#include <cstddef>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>

#include "src/GameManager.h"
#include "src/PhysicsManager.h"

class Game {
public:
    Game();
    void run();

private:
    enum class ScreenState {
        MainMenu,
        Settings,
        Game
    }; //What page the application is curently on

    enum class GameState {
        Playing,
        Paused,
        Won,
        GameOver
    }; //what state the game is in while playing

    struct Brick {
        sf::RectangleShape shape;
        bool isActive = true;
    }; //Struct that handles the bricks to be shown in the menu. 

    void initialize();
    void initializeBricks();
    void resetBricks();
    void resetGame();
    void handleEvents();
    void handleInput(float dt);
    void update(float dt);
    void resetBall();
    void applyBallLaunchVelocity();
    void render();
    void renderMainMenu();
    void renderSettingsScreen();
    void renderBricks();
    void updateHudText();
    void processKeyPressed(const sf::Event::KeyPressed& key);
    void pollKeyboardShortcuts();
    void handleMouseEvent();
    bool ballIntersectsBrick(const Brick& brick) const;
    void handleBrickCollision(float dt);
    void drawBorders();
    void loadAndPlayMusic();
    void loadOtherSFX();
    void setMusicVolume();
    float getMusicVolume();

    sf::Clock frameClock_;
    sf::RenderWindow window;
    sf::RectangleShape paddle;
    sf::CircleShape ball;
    sf::Font hudFont;
    sf::Music bkgMusic;
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> livesText;
    std::optional<sf::Text> statusText;
    bool hasHudFont = false;
    std::optional<sf::Text> menuTitleText;
    std::optional<sf::Text> menuLineText;
    sf::RectangleShape playBtn;
    sf::RectangleShape settingsBtn;
    sf::RectangleShape quitBtn;
    sf::RectangleShape settingsRtnBtn;
    ScreenState screenState = ScreenState::MainMenu;
    int mainMenuSelection = 0;
    int settingsSelection = 0;
    float paddleSpeedMultiplier = 1.f;
    float ballSpeedMultiplier = 1.f;
    std::vector<Brick> bricks;
    int score = 0;
    GameState gameState = GameState::Playing;
    std::optional<std::size_t> collidingBrickIndex;
    PhysicsManager physicsManager;
    GameManager gameManager;
    
    std::string musicFPath = "assets/audio/mondamusic-retro-arcade-game-music-512837.wav";
    float musicVolume = 50.f;

    std::string btnAudioFPath = "assets/audio/mouse-click-negative-click-jam-fx-1-00-00.wav";
    sf::SoundBuffer buttonSoundBuffer;
    std::optional<sf::Sound> btnSound;

    std::string brickDestroyFPath = "";
    sf::SoundBuffer brickSoundBuffer;
    std::optional<sf::Sound> brickSound;
    bool brickSoundLoaded = false;

    std::string ballBounceFPath = "";
    sf::SoundBuffer bounceSoundBuffer;
    std::optional<sf::Sound> bounceSound;
    bool bounceSoundLoaded = false;

    bool prevEscDown_ = false;
    bool prevMDown_ = false;
    bool prevRDown_ = false;
    bool prevSpaceDown_ = false;
};
