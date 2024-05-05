#include "RedFood.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>

// [AGENT 4 ADDITION — implementation of RedFood constructor and applyEffect]

const float RED_FALL_SPEED = 150.f;
const float RED_FOOD_WIDTH = 30.f;
const float RED_FOOD_HEIGHT = 15.f;

RedFood::RedFood(float x, float y)
    : Food(x, y, RED_FALL_SPEED, sf::Vector2f(RED_FOOD_WIDTH, RED_FOOD_HEIGHT)) {
    shape.setSize(sf::Vector2f(RED_FOOD_WIDTH, RED_FOOD_HEIGHT));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(sf::Vector2f(RED_FOOD_WIDTH / 2.f, RED_FOOD_HEIGHT / 2.f));
    shape.setPosition(position);
}

void RedFood::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void RedFood::applyEffect(Paddle& lower, 
                           Paddle* upper, 
                           std::vector<Ball>& balls, 
                           float& redTimer,
                           float windowWidth) {
    for (Ball& b : balls) {
        if (b.isActive()) {
            b.multiplySpeed(1.5f); // Multiply speed by 1.5x
        }
    }
    redTimer = 5.0f; // 5-second countdown
}

std::string RedFood::getType() const {
    return "RedFood";
}
