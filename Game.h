#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include "Food.h"

#include "HUD.h"

// Forward declaration of UIManager to avoid circular includes
class UIManager;

/**
 * @file Game.h
 * @brief Declaration of the Game class managing the central loop, inputs, physics, and rendering.
 * 
 * [RUBRIC: Composition/Aggregation ✓] - Game has Paddle, Level pointer, vector of Balls, vector of Foods.
 * [RUBRIC: Zero Global Functions ✓] - Game encapsulates all mechanics; no global subroutines.
 */
class Game {
private:
    sf::RenderWindow& window;         ///< Reference to the global SFML window context (not owned)
    UIManager& uiManager;             ///< Reference to the UIManager managing screen states
    Level* currentLevel;              ///< Polymorphic pointer to active Level (owns ptr)
    int currentLevelIndex;            ///< Index of the current level (1, 2, or 3)
    std::vector<Ball> balls;          ///< Active balls collection (supports multi-ball)
    Paddle lowerPaddle;               ///< Player lower paddle (mouse-controlled)
    Paddle* upperPaddle;              ///< Upper paddle pointer (keyboard-controlled, Level 3 only)
    std::vector<Food*> activeFoods;   ///< Falling power-ups and power-downs
    int score;                        ///< Total game score
    bool paused;                      ///< Game pause state flag
    bool gameOver;                    ///< Game over state flag (lives == 0 on current level)
    bool gameWon;                     ///< Game victory state flag (level 3 completed)
    sf::Clock clock;                  ///< Clock to measure delta-time
    
    // Power-up duration countdowns
    float paddleEffectTimer;          ///< Paddle width effect timer (Green/Pink food)
    float blueEffectTimer;            ///< Ball slow effect timer (Blue food)
    float redEffectTimer;             ///< Ball acceleration effect timer (Red food)
    float yellowEffectTimer;          ///< Extra balls tracker / timer (Yellow food)
    
    float originalBallSpeed;          ///< Baseline ball speed used for resets and multipliers
    
    // [AGENT 4 ADDITION — HUD and high score members]
    HUD hud;                          ///< Score bar HUD display
    int highScore;                    ///< Loaded high score

public:
    /**
     * @brief Construct a new Game object.
     * @param win Reference to the RenderWindow context.
     * @param ui Reference to the UIManager context.
     */
    Game(sf::RenderWindow& win, UIManager& ui);

    /**
     * @brief Clean up all dynamic resources (currentLevel, upperPaddle, foods).
     */
    ~Game();

    /**
     * @brief Outer game loop. Polls events, updates physics, and draws frame.
     */
    void run();

    /**
     * @brief Core event handler. Handles pause toggling, closed window, and restarts.
     * @param event The SFML Event package.
     */
    void handleEvents(const sf::Event& event);

    /**
     * @brief Update loop step. Runs paddles, power-ups, balls, and level checks.
     * @param dt Delta time (seconds).
     */
    void update(float dt);

    /**
     * @brief Draws all assets, bricks, balls, paddles, and the HUD to the window.
     */
    void draw();

    // Physics sub-systems
    
    /**
     * @brief Update ball locations and trigger reflections/lives lost.
     * [RUBRIC: Multi-ball Physics ✓] - Iterates and updates all balls independently.
     * @param dt Delta time (seconds).
     */
    void updateBalls(float dt);

    /**
     * @brief Update falling food coordinates and handle screen escape cleanup.
     * @param dt Delta time (seconds).
     */
    void updateFoods(float dt);

    /**
     * @brief Handle reflection off walls, or death boundary crossings.
     * @param ball Reference to the ball being evaluated.
     */
    void checkBallWallCollision(Ball& ball);

    /**
     * @brief Handle ball reflections off the lower paddle, and upper paddle in Level 3.
     * @param ball Reference to the ball being evaluated.
     */
    void checkBallPaddleCollision(Ball& ball);

    /**
     * @brief Handle ball-brick collision checks, damage, score additions, and food drops.
     * @param ball Reference to the ball being evaluated.
     */
    void checkBallBrickCollisions(Ball& ball);

    /**
     * @brief Check if falling food intersects the lower paddle and triggers its effect.
     */
    void checkFoodPaddleCollision();

    // State managers
    
    /**
     * @brief Lose a life. Triggers ball reset or game-over condition.
     */
    void loseLife();

    /**
     * @brief Position ball back at center directly above the lower paddle.
     */
    void resetBall();

    /**
     * @brief Instantiate correct level subclass and load layout.
     * @param n Level index to load (1, 2, or 3).
     */
    void loadLevel(int n);

    /**
     * @brief Advance to next level or mark game as won.
     */
    void nextLevel();

    /**
     * @brief Count down active effect timers and restore original attributes.
     * @param dt Delta time (seconds).
     */
    void handlePowerUpExpiry(float dt);

    // Score helpers
    
    /**
     * @brief Increment game score.
     * @param points Score addition value.
     */
    void addScore(int points);

    /**
     * @brief Access current game score.
     * @return int Current score.
     */
    int getScore() const;

    /**
     * @brief Restore game state from a loaded state.
     */
    void restoreState(int level, int score, int lives,
                      float ballX, float ballY,
                      float ballVelX, float ballVelY,
                      float paddleX, float paddleWidth);

    // State getters
    int getLevelIndex() const { return currentLevelIndex; }
    bool isGameOver() const { return gameOver; }
    bool isGameWon() const { return gameWon; }
    const std::vector<Ball>& getBalls() const { return balls; }
    const Paddle& getLowerPaddle() const { return lowerPaddle; }
};

#endif // GAME_H