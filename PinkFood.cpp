#include "PinkFood.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

// [AGENT 4 ADDITION — implementation of PinkFood constructor and applyEffect]

const float FOOD_FALL_SPEED = 150.f;
const float PINK_FOOD_WIDTH = 20.f;
const float PINK_FOOD_HEIGHT = 20.f;

PinkFood::PinkFood(float x, float y)
    : Food(x, y, FOOD_FALL_SPEED, sf::Vector2f(PINK_FOOD_WIDTH, PINK_FOOD_HEIGHT)) {
    shape.setSize(sf::Vector2f(PINK_FOOD_WIDTH, PINK_FOOD_HEIGHT));
    shape.setFillColor(sf::Color(255, 105, 180)); // Hot Pink
    shape.setOrigin(sf::Vector2f(PINK_FOOD_WIDTH / 2.f, PINK_FOOD_HEIGHT / 2.f));
    shape.setPosition(position);
}

void PinkFood::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void PinkFood::applyEffect(Paddle& lower, 
                            Paddle* upper, 
                            std::vector<Ball>& balls, 
                            float& effectTimer,
                            float windowWidth) {
    const float MIN_PADDLE_WIDTH = 30.f;
    
    // Halve width but floor at MIN_PADDLE_WIDTH (30px)
    float newW = lower.getWidth() / 2.f;
    lower.setWidth(std::max(newW, MIN_PADDLE_WIDTH));
    lower.clampToWindow(windowWidth);
    
    if (upper != nullptr) {
        float newUpperW = upper->getWidth() / 2.f;
        upper->setWidth(std::max(newUpperW, MIN_PADDLE_WIDTH));
        upper->clampToWindow(windowWidth);
    }
    
    // Size changes are permanent until next green/pink food
    effectTimer = 0.f;
}

std::string PinkFood::getType() const {
    return "PinkFood";
}
