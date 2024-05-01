#include "GreenBrick.h"
#include "GreenFood.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file GreenBrick.cpp
 * @brief Implementation of GreenBrick methods.
 */

GreenBrick::GreenBrick(float x, float y)
    : Brick(x, y, 1, sf::Color::Green) {}

GreenBrick::GreenBrick(const GreenBrick& other)
    : Brick(other) {}

void GreenBrick::takeDamage() {
    if (destroyed) return;
    
    hitPoints--;
    if (hitPoints <= 0) {
        destroyed = true;
    } else {
        triggerHitFlash();
    }
}

Food* GreenBrick::dropFood() {
    // Return heap-allocated GreenFood centered horizontally and vertically on the brick
    return new GreenFood(position.x + BRICK_WIDTH / 2.f, position.y + BRICK_HEIGHT / 2.f);
}

void GreenBrick::draw(sf::RenderWindow& win) {
    drawBrick(win);
}

int GreenBrick::getScoreValue() const {
    return 10; // Green Brick is worth 10 points
}
