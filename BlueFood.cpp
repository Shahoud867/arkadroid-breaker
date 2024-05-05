#include "BlueFood.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>

// [AGENT 4 ADDITION — implementation of BlueFood constructor and applyEffect]

const float BLUE_FALL_SPEED = 150.f;
const float BLUE_CIRCLE_RADIUS = 10.f;

BlueFood::BlueFood(float x, float y)
    : Food(x, y, BLUE_FALL_SPEED, sf::Vector2f(BLUE_CIRCLE_RADIUS * 2.f, BLUE_CIRCLE_RADIUS * 2.f)) {
    shape.setRadius(BLUE_CIRCLE_RADIUS);
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(sf::Vector2f(BLUE_CIRCLE_RADIUS, BLUE_CIRCLE_RADIUS));
    shape.setPosition(position);
}

void BlueFood::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void BlueFood::applyEffect(Paddle& lower, 
                            Paddle* upper, 
                            std::vector<Ball>& balls, 
                            float& blueTimer,
                            float windowWidth) {
    for (Ball& b : balls) {
        if (b.isActive()) {
            b.multiplySpeed(0.5f); // Halve speed
        }
    }
    blueTimer = 5.0f; // 5-second countdown
}

std::string BlueFood::getType() const {
    return "BlueFood";
}
