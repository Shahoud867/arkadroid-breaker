#include "Game.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "GreenFood.h"
#include "PinkFood.h"
#include "BlueFood.h"
#include "RedFood.h"
#include "YellowFood.h"
#include "UIManager.h"
#include "FileHandler.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

/**
 * @file Game.cpp
 * @brief Implementation of the Game class methods managing the Arkadroid engine.
 */

Game::Game(sf::RenderWindow& win, UIManager& ui)
    : window(win),
      uiManager(ui),
      currentLevel(nullptr),
      currentLevelIndex(1),
      lowerPaddle(static_cast<float>(win.getSize().x) / 2.f, static_cast<float>(win.getSize().y) - 30.f, 120.f, 20.f, false),
      upperPaddle(nullptr),
      score(0),
      paused(false),
      gameOver(false),
      gameWon(false),
      paddleEffectTimer(0.f),
      blueEffectTimer(0.f),
      redEffectTimer(0.f),
      yellowEffectTimer(0.f),
      originalBallSpeed(300.f),
      hud("23i-2515", ui.getPlayerName()),
      highScore(0) {
    
    // Seed random number generator for randomized brick selections
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Load high score
    auto scores = FileHandler::loadScores();
    if (!scores.empty()) {
        highScore = scores[0].second;
    }
    
    // Start by loading Level 1
    loadLevel(1);
}

Game::~Game() {
    delete currentLevel;
    delete upperPaddle;
    for (Food* f : activeFoods) {
        delete f;
    }
    activeFoods.clear();
}

void Game::run() {
    clock.restart();
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        // Prevent huge movement spikes (e.g. from debugging, focus switching, or loading lag)
        if (dt > 0.1f) {
            dt = 0.1f;
        }

        // [SFML 2.x Compatible event polling]
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvents(event);
        }

        // Return if player chose Save & Quit or Main Menu from the Pause overlay
        if (uiManager.getState() == GameState::MAIN_MENU) {
            return;
        }

        update(dt);

        // Exit run loop when game is over or won to trigger Game Over / Victory UI screen
        if (gameOver || gameWon) {
            uiManager.setState(gameOver ? GameState::GAME_OVER : GameState::GAME_WON);
            return;
        }

        draw();
    }
}

void Game::handleEvents(const sf::Event& event) {
    // [SFML 2.x Compatible event type checking]
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    
    // Check key presses
    if (event.type == sf::Event::KeyPressed) {
        // Toggle pause mode with Escape or P key
        if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape) {
            paused = !paused;
        }
        
        // Restart entire game from Level 1
        if (event.key.code == sf::Keyboard::R && (gameOver || gameWon)) {
            score = 0;
            gameOver = false;
            gameWon = false;
            loadLevel(1);
        }
    }

    // Handle mouse hovering/clicking on the pause screen when paused
    if (paused) {
        if (event.type == sf::Event::MouseMoved) {
            uiManager.handlePauseScreenHover(window, sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                int choice = uiManager.handlePauseScreenClick(window, mousePos);
                if (choice == 1) {
                    // Resume
                    paused = false;
                }
                else if (choice == 2) {
                    // Save & Quit
                    if (!balls.empty()) {
                        FileHandler::saveGameState(
                            uiManager.getPlayerName(),
                            currentLevelIndex,
                            score,
                            currentLevel ? currentLevel->getLives() : 2,
                            balls[0].getPosition().x,
                            balls[0].getPosition().y,
                            balls[0].getVelocity().x,
                            balls[0].getVelocity().y,
                            lowerPaddle.getPosition().x,
                            lowerPaddle.getWidth()
                        );
                    }
                    uiManager.setState(GameState::MAIN_MENU);
                }
                else if (choice == 3) {
                    // Main Menu
                    uiManager.setState(GameState::MAIN_MENU);
                }
            }
        }
    }
}

void Game::update(float dt) {
    if (paused || gameOver || gameWon) {
        return;
    }

    // 1. Update paddle positions (mouse control for lower, keyboard W/R for upper)
    lowerPaddle.updateMouse(window);
    lowerPaddle.clampToWindow(static_cast<float>(window.getSize().x));
    
    if (upperPaddle != nullptr) {
        bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
        upperPaddle->updateKeyboard(dt, moveLeft, moveRight);
        upperPaddle->clampToWindow(static_cast<float>(window.getSize().x));
    }

    // 2. Decrement powerup timer durations and apply restorations
    handlePowerUpExpiry(dt);

    // 3. Update brick flashing states
    if (currentLevel) {
        for (Brick* b : currentLevel->getBricks()) {
            if (b && !b->isDestroyed()) {
                b->updateFlash(dt);
            }
        }
    }

    // 4. Update balls & process collisions/out-of-bounds
    updateBalls(dt);

    // 5. Update foods falling downward
    updateFoods(dt);

    // 6. Check for level completion
    if (currentLevel && currentLevel->isComplete()) {
        nextLevel();
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);

    // 1. Draw bricks
    if (currentLevel) {
        currentLevel->draw(window);
    }

    // 2. Draw paddles
    lowerPaddle.draw(window);
    if (upperPaddle != nullptr) {
        upperPaddle->draw(window);
    }

    // 3. Draw active balls
    for (auto& ball : balls) {
        if (ball.isActive()) {
            ball.draw(window);
        }
    }

    // 4. Draw falling foods
    for (auto* food : activeFoods) {
        if (food->isActive()) {
            food->draw(window);
        }
    }

    // 5. Draw HUD using the modern HUD class
    hud.update(score, highScore, currentLevelIndex, currentLevel ? currentLevel->getLives() : 0);
    hud.draw(window);

    // Draw pause screen overlay when paused
    if (paused) {
        uiManager.drawPauseScreen(window, score);
    }

    window.display();
}

void Game::updateBalls(float dt) {
    bool anyBallActive = false;
    
    for (auto& ball : balls) {
        if (ball.isActive()) {
            ball.update(dt);
            checkBallWallCollision(ball);
            
            if (ball.isActive()) {
                checkBallPaddleCollision(ball);
                checkBallBrickCollisions(ball);
                anyBallActive = true;
            }
        }
    }
    
    if (!anyBallActive) {
        loseLife();
    }
}

void Game::updateFoods(float dt) {
    for (auto* food : activeFoods) {
        if (food->isActive()) {
            food->update(dt);
            if (food->getBounds().top > static_cast<float>(window.getSize().y)) {
                food->collect();
            }
        }
    }

    checkFoodPaddleCollision();

    activeFoods.erase(
        std::remove_if(activeFoods.begin(), activeFoods.end(), [](Food* f) {
            if (!f->isActive()) {
                delete f;
                return true;
            }
            return false;
        }),
        activeFoods.end()
    );
}

void Game::checkBallWallCollision(Ball& ball) {
    sf::FloatRect bounds = ball.getBounds();
    float winW = static_cast<float>(window.getSize().x);
    float winH = static_cast<float>(window.getSize().y);

    if (bounds.left <= 0.f && ball.getVelocity().x < 0.f) {
        ball.reflectX();
    }
    else if (bounds.left + bounds.width >= winW && ball.getVelocity().x > 0.f) {
        ball.reflectX();
    }

    if (currentLevelIndex == 3) {
        if (bounds.top + bounds.height < 0.f) {
            ball.setActive(false);
        }
    } else {
        if (bounds.top <= 0.f && ball.getVelocity().y < 0.f) {
            ball.reflectY();
        }
    }

    if (bounds.top > winH) {
        ball.setActive(false);
    }
}

void Game::checkBallPaddleCollision(Ball& ball) {
    if (ball.getVelocity().y > 0.f && ball.getBounds().intersects(lowerPaddle.getBounds())) {
        float ballX = ball.getBounds().left + ball.getBounds().width / 2.f;
        float paddleX = lowerPaddle.getBounds().left + lowerPaddle.getBounds().width / 2.f;
        float paddleWidth = lowerPaddle.getBounds().width;
        
        float hitOffset = (ballX - paddleX) / paddleWidth;
        hitOffset = std::max(-0.5f, std::min(0.5f, hitOffset));
        
        float currentSpeed = ball.getSpeed();
        const float MAX_ANGLE_SPEED = currentSpeed * 1.5f;
        float newDx = hitOffset * MAX_ANGLE_SPEED;
        
        float maxDx = currentSpeed * 0.85f;
        if (newDx > maxDx) newDx = maxDx;
        if (newDx < -maxDx) newDx = -maxDx;
        
        float newDy = -std::sqrt(currentSpeed * currentSpeed - newDx * newDx);
        ball.setVelocity(sf::Vector2f(newDx, newDy));
        
        lowerPaddle.setColor(ball.getColor());
    }

    if (currentLevelIndex == 3 && upperPaddle != nullptr) {
        if (ball.getVelocity().y < 0.f && ball.getBounds().intersects(upperPaddle->getBounds())) {
            float ballX = ball.getBounds().left + ball.getBounds().width / 2.f;
            float paddleX = upperPaddle->getBounds().left + upperPaddle->getBounds().width / 2.f;
            float paddleWidth = upperPaddle->getBounds().width;
            
            float hitOffset = (ballX - paddleX) / paddleWidth;
            hitOffset = std::max(-0.5f, std::min(0.5f, hitOffset));
            
            float currentSpeed = ball.getSpeed();
            const float MAX_ANGLE_SPEED = currentSpeed * 1.5f;
            float newDx = hitOffset * MAX_ANGLE_SPEED;
            
            float maxDx = currentSpeed * 0.85f;
            if (newDx > maxDx) newDx = maxDx;
            if (newDx < -maxDx) newDx = -maxDx;
            
            float newDy = std::sqrt(currentSpeed * currentSpeed - newDx * newDx);
            ball.setVelocity(sf::Vector2f(newDx, newDy));
            
            upperPaddle->setColor(ball.getColor());
        }
    }
}

void Game::checkBallBrickCollisions(Ball& ball) {
    if (!currentLevel) return;

    std::vector<Brick*>& levelBricks = currentLevel->getBricks();
    bool hitOccurred = false;

    for (size_t i = 0; i < levelBricks.size(); ++i) {
        Brick* brick = levelBricks[i];
        if (brick && !brick->isDestroyed() && ball.getBounds().intersects(brick->getBounds())) {
            Ball::HitSide side = ball.detectCollisionSide(brick->getBounds());
            if (side != Ball::HitSide::NONE) {
                if (side == Ball::HitSide::LEFT || side == Ball::HitSide::RIGHT) {
                    ball.reflectX();
                } else if (side == Ball::HitSide::TOP || side == Ball::HitSide::BOTTOM) {
                    ball.reflectY();
                }

                brick->takeDamage();
                ball.setColor(brick->getColor());

                if (brick->isDestroyed()) {
                    addScore(brick->getScoreValue());
                    Food* f = brick->dropFood();
                    if (f != nullptr) {
                        activeFoods.push_back(f);
                    }
                }
                
                hitOccurred = true;
                break;
            }
        }
    }

    if (hitOccurred) {
        levelBricks.erase(
            std::remove_if(levelBricks.begin(), levelBricks.end(), [](Brick* b) {
                if (b && b->isDestroyed()) {
                    delete b;
                    return true;
                }
                return false;
            }),
            levelBricks.end()
        );
    }
}

void Game::checkFoodPaddleCollision() {
    for (auto* food : activeFoods) {
        if (food->isActive() && food->getBounds().intersects(lowerPaddle.getBounds())) {
            food->collect();
            
            std::string type = food->getType();
            float winW = static_cast<float>(window.getSize().x);
            if (type == "GreenFood" || type == "PinkFood") {
                food->applyEffect(lowerPaddle, upperPaddle, balls, paddleEffectTimer, winW);
            } else if (type == "BlueFood") {
                // Cancel existing speed effects first
                if (redEffectTimer > 0.f) {
                    for (auto& b : balls) b.multiplySpeed(1.f / 1.5f);
                    redEffectTimer = 0.f;
                }
                food->applyEffect(lowerPaddle, upperPaddle, balls, blueEffectTimer, winW);
            } else if (type == "RedFood") {
                if (blueEffectTimer > 0.f) {
                    for (auto& b : balls) b.multiplySpeed(2.f);
                    blueEffectTimer = 0.f;
                }
                food->applyEffect(lowerPaddle, upperPaddle, balls, redEffectTimer, winW);
            } else if (type == "YellowFood") {
                food->applyEffect(lowerPaddle, upperPaddle, balls, yellowEffectTimer, winW);
            }
        }
    }
}

void Game::loseLife() {
    if (currentLevel) {
        currentLevel->decrementLife();
        
        if (currentLevel->isGameOver()) {
            gameOver = true;
        } else {
            paddleEffectTimer = 0.f;
            blueEffectTimer = 0.f;
            redEffectTimer = 0.f;
            yellowEffectTimer = 0.f;
            lowerPaddle.resetWidth();
            if (upperPaddle) {
                upperPaddle->resetWidth();
            }
            resetBall();
        }
    }
}

void Game::resetBall() {
    balls.clear();
    
    float radius = 10.f;
    float speed = originalBallSpeed * (currentLevel ? currentLevel->getBallSpeedMultiplier() : 1.f);
    
    float x = lowerPaddle.getBounds().left + lowerPaddle.getBounds().width / 2.f;
    float y = lowerPaddle.getBounds().top - radius - 5.f;
    
    balls.push_back(Ball(x, y, radius, speed));
}

void Game::loadLevel(int n) {
    delete currentLevel;
    currentLevel = nullptr;
    
    delete upperPaddle;
    upperPaddle = nullptr;
    
    for (Food* f : activeFoods) {
        delete f;
    }
    activeFoods.clear();
    
    currentLevelIndex = n;
    
    paddleEffectTimer = 0.f;
    blueEffectTimer = 0.f;
    redEffectTimer = 0.f;
    yellowEffectTimer = 0.f;
    lowerPaddle.resetWidth();
    
    if (n == 1) {
        currentLevel = new Level1();
    } else if (n == 2) {
        currentLevel = new Level2();
    } else if (n == 3) {
        currentLevel = new Level3();
        upperPaddle = new Paddle(static_cast<float>(window.getSize().x) / 2.f, 50.f, 120.f, 20.f, true);
        static_cast<Level3*>(currentLevel)->setUpperPaddleRef(upperPaddle);
    }
    
    if (currentLevel) {
        currentLevel->generatePattern(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    }
    
    resetBall();
}

void Game::nextLevel() {
    if (currentLevelIndex < 3) {
        loadLevel(currentLevelIndex + 1);
    } else {
        gameWon = true;
    }
}

void Game::handlePowerUpExpiry(float dt) {
    if (paddleEffectTimer > 0.f) {
        paddleEffectTimer -= dt;
        if (paddleEffectTimer <= 0.f) {
            lowerPaddle.resetWidth();
            if (upperPaddle) {
                upperPaddle->resetWidth();
            }
            paddleEffectTimer = 0.f;
        }
    }

    if (blueEffectTimer > 0.f) {
        blueEffectTimer -= dt;
        if (blueEffectTimer <= 0.f) {
            for (auto& ball : balls) {
                if (ball.isActive()) {
                    ball.multiplySpeed(2.f);
                }
            }
            blueEffectTimer = 0.f;
        }
    }

    if (redEffectTimer > 0.f) {
        redEffectTimer -= dt;
        if (redEffectTimer <= 0.f) {
            for (auto& ball : balls) {
                if (ball.isActive()) {
                    ball.multiplySpeed(1.f / 1.5f);
                }
            }
            redEffectTimer = 0.f;
        }
    }

    if (yellowEffectTimer > 0.f) {
        yellowEffectTimer -= dt;
        if (yellowEffectTimer <= 0.f) {
            yellowEffectTimer = 0.f;
        }
    }
}

void Game::addScore(int points) {
    score += points;
}

int Game::getScore() const {
    return score;
}

void Game::restoreState(int level, int score, int lives,
                        float ballX, float ballY,
                        float ballVelX, float ballVelY,
                        float paddleX, float paddleWidth) {
    this->score = score;
    this->gameOver = false;
    this->gameWon = false;
    this->paused = false;
    
    loadLevel(level);
    if (currentLevel) {
        currentLevel->setLives(lives);
    }
    
    lowerPaddle.setPosition(sf::Vector2f(paddleX, lowerPaddle.getPosition().y));
    lowerPaddle.setWidth(paddleWidth);
    
    if (upperPaddle) {
        upperPaddle->setWidth(paddleWidth);
    }

    balls.clear();
    float radius = 10.f;
    float speed = originalBallSpeed * (currentLevel ? currentLevel->getBallSpeedMultiplier() : 1.f);
    Ball ball(ballX, ballY, radius, speed);
    ball.setPosition(sf::Vector2f(ballX, ballY));
    ball.setVelocity(sf::Vector2f(ballVelX, ballVelY));
    balls.push_back(ball);
}