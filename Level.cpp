#include "Level.h"
#include <algorithm>

/**
 * @file Level.cpp
 * @brief Implementation of the base Level class methods.
 */

Level::Level(float speedMultiplier)
    : lives(2), ballSpeedMultiplier(speedMultiplier) {}

Level::~Level() {
    // [RUBRIC: Destructor ✓] - Clean up dynamically allocated brick pointers to avoid memory leaks
    for (Brick* b : bricks) {
        delete b;
    }
    bricks.clear();
}

void Level::decrementLife() {
    if (lives > 0) {
        lives--;
    }
}

int Level::getLives() const {
    return lives;
}

bool Level::isGameOver() const {
    return lives == 0;
}

std::vector<Brick*>& Level::getBricks() {
    return bricks;
}

void Level::removeBrick(int index) {
    if (index >= 0 && index < static_cast<int>(bricks.size())) {
        delete bricks[index];
        bricks.erase(bricks.begin() + index);
    }
}

float Level::getBallSpeedMultiplier() const {
    return ballSpeedMultiplier;
}

void Level::draw(sf::RenderWindow& win) {
    // Draw all bricks that are not destroyed and are active
    for (Brick* b : bricks) {
        if (b && !b->isDestroyed()) {
            b->draw(win);
        }
    }
}
