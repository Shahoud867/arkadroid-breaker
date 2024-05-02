#include "PinkBrick.h"
#include "PinkFood.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file PinkBrick.cpp
 * @brief Implementation of PinkBrick methods.
 */

PinkBrick::PinkBrick(float x, float y)
    : Brick(x, y, 2, sf::Color(255, 105, 180)) {} // Hot Pink color

PinkBrick::PinkBrick(const PinkBrick& other)
    : Brick(other) {}

void PinkBrick::takeDamage() {
    if (destroyed) return;
    
    hitPoints--;
    if (hitPoints <= 0) {
        destroyed = true;
    } else {
        triggerHitFlash();
    }
}

Food* PinkBrick::dropFood() {
    return new PinkFood(position.x + BRICK_WIDTH / 2.f, position.y + BRICK_HEIGHT / 2.f);
}

void PinkBrick::draw(sf::RenderWindow& win) {
    drawBrick(win);
}

int PinkBrick::getScoreValue() const {
    return 20;
}
