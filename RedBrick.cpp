#include "RedBrick.h"
#include "RedFood.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file RedBrick.cpp
 * @brief Implementation of RedBrick methods.
 */

RedBrick::RedBrick(float x, float y)
    : Brick(x, y, 3, sf::Color::Red) {}

RedBrick::RedBrick(const RedBrick& other)
    : Brick(other) {}

void RedBrick::takeDamage() {
    if (destroyed) return;
    
    hitPoints--;
    if (hitPoints <= 0) {
        destroyed = true;
    } else {
        triggerHitFlash();
    }
}

Food* RedBrick::dropFood() {
    return new RedFood(position.x + BRICK_WIDTH / 2.f, position.y + BRICK_HEIGHT / 2.f);
}

void RedBrick::draw(sf::RenderWindow& win) {
    drawBrick(win);
}

int RedBrick::getScoreValue() const {
    return 30;
}
