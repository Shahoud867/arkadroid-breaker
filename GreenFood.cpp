#include "GreenFood.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

// [AGENT 4 ADDITION — implementation of GreenFood constructor and applyEffect]

const float FOOD_FALL_SPEED = 150.f;
const float GREEN_FOOD_WIDTH = 20.f;
const float GREEN_FOOD_HEIGHT = 20.f;

GreenFood::GreenFood(float x, float y)
    : Food(x, y, FOOD_FALL_SPEED, sf::Vector2f(GREEN_FOOD_WIDTH, GREEN_FOOD_HEIGHT)) {
    shape.setPointCount(3);
    
    // Triangular shape
    shape.setPoint(0, sf::Vector2f(GREEN_FOOD_WIDTH / 2.f, 0.f));
    shape.setPoint(1, sf::Vector2f(0.f, GREEN_FOOD_HEIGHT));
    shape.setPoint(2, sf::Vector2f(GREEN_FOOD_WIDTH, GREEN_FOOD_HEIGHT));
    shape.setFillColor(sf::Color::Green);
    
    shape.setOrigin(sf::Vector2f(GREEN_FOOD_WIDTH / 2.f, GREEN_FOOD_HEIGHT / 2.f));
    shape.setPosition(position);
}

void GreenFood::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void GreenFood::applyEffect(Paddle& lower, 
                             Paddle* upper, 
                             std::vector<Ball>& balls, 
                             float& effectTimer,
                             float windowWidth) {
    float maxW = windowWidth - 20.f;
    
    // Double width and clamp to max width
    lower.setWidth(std::min(lower.getWidth() * 2.0f, maxW));
    lower.clampToWindow(windowWidth);
    
    if (upper != nullptr) {
        upper->setWidth(std::min(upper->getWidth() * 2.0f, maxW));
        upper->clampToWindow(windowWidth);
    }
    
    // Permanent until next size change; no timer runs
    effectTimer = 0.f;
}

std::string GreenFood::getType() const {
    return "GreenFood";
}
