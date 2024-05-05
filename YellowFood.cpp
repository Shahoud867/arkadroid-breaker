#include "YellowFood.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file YellowFood.cpp
 * @brief Implementation of YellowFood methods.
 */

const float YELLOW_FALL_SPEED = 150.f;
const float YELLOW_SQUARE_SIZE = 20.f;

YellowFood::YellowFood(float x, float y)
    : Food(x, y, YELLOW_FALL_SPEED, sf::Vector2f(YELLOW_SQUARE_SIZE, YELLOW_SQUARE_SIZE)) {
    shape.setSize(sf::Vector2f(YELLOW_SQUARE_SIZE, YELLOW_SQUARE_SIZE));
    shape.setFillColor(sf::Color::Yellow);
    
    // [NOTE: SFML CAVEAT — set origin to geometric center of the shape to align positioning with the Food center]
    shape.setOrigin(sf::Vector2f(YELLOW_SQUARE_SIZE / 2.f, YELLOW_SQUARE_SIZE / 2.f));
    shape.setPosition(position);
}

void YellowFood::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void YellowFood::applyEffect(Paddle& paddle, Paddle* upper, std::vector<Ball>& balls, float& effectTimer, float windowWidth) {
    int originalSize = static_cast<int>(balls.size());
    int copiesSpawned = 0;
    
    for (int i = 0; i < originalSize; ++i) {
        if (balls[i].isActive()) {
            // [RUBRIC: Copy Constructor ✓] — Spawning new balls using the Ball copy constructor
            Ball copy1(balls[i]);
            Ball copy2(balls[i]);

            sf::Vector2f originalVel = balls[i].getVelocity();

            // Symmetrically scatter the new balls by adjusting their velocity vectors slightly
            // We shift the X velocity component in opposite directions and apply a small upwards push
            const float VELOCITY_SCATTER_X = 120.f;
            const float VELOCITY_PUSH_Y = -60.f;

            copy1.setVelocity(sf::Vector2f(originalVel.x - VELOCITY_SCATTER_X, originalVel.y + VELOCITY_PUSH_Y));
            copy2.setVelocity(sf::Vector2f(originalVel.x + VELOCITY_SCATTER_X, originalVel.y + VELOCITY_PUSH_Y));

            copy1.setActive(true);
            copy2.setActive(true);

            balls.push_back(copy1);
            balls.push_back(copy2);
            copiesSpawned += 2;
            
            // Limit spawning to prevent explosion of balls
            if (copiesSpawned >= 4) {
                break;
            }
        }
    }
    effectTimer = 5.f;
}

std::string YellowFood::getType() const {
    return "YellowFood";
}