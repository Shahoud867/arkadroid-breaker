#include "BlueBrick.h"
#include "BlueFood.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file BlueBrick.cpp
 * @brief Implementation of BlueBrick methods.
 */

BlueBrick::BlueBrick(float x, float y)
    : Brick(x, y, 3, sf::Color::Blue) {}

BlueBrick::BlueBrick(const BlueBrick& other)
    : Brick(other) {}

void BlueBrick::takeDamage() {
    if (destroyed) return;
    
    hitPoints--;
    if (hitPoints <= 0) {
        destroyed = true;
    } else {
        triggerHitFlash();
    }
}

Food* BlueBrick::dropFood() {
    return new BlueFood(position.x + BRICK_WIDTH / 2.f, position.y + BRICK_HEIGHT / 2.f);
}

void BlueBrick::draw(sf::RenderWindow& win) {
    drawBrick(win);
}

int BlueBrick::getScoreValue() const {
    return 30;
}
