#include "YellowBrick.h"
#include "YellowFood.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file YellowBrick.cpp
 * @brief Implementation of YellowBrick methods.
 */

YellowBrick::YellowBrick(float x, float y)
    : Brick(x, y, 2, sf::Color::Yellow) {}

YellowBrick::YellowBrick(const YellowBrick& other)
    : Brick(other) {}

void YellowBrick::takeDamage() {
    if (destroyed) return;
    
    hitPoints--;
    if (hitPoints <= 0) {
        destroyed = true;
    } else {
        triggerHitFlash();
    }
}

Food* YellowBrick::dropFood() {
    return new YellowFood(position.x + BRICK_WIDTH / 2.f, position.y + BRICK_HEIGHT / 2.f);
}

void YellowBrick::draw(sf::RenderWindow& win) {
    drawBrick(win);
}

int YellowBrick::getScoreValue() const {
    return 20;
}
