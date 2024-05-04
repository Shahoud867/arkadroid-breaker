#ifndef GREENFOOD_H
#define GREENFOOD_H

#include "Food.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file GreenFood.h
 * @brief Subclass representing Green Food (Power-up: expands paddle width).
 */
class GreenFood : public Food {
private:
    sf::ConvexShape shape; ///< Convex shape representing the triangle

public:
    GreenFood(float x, float y);
    void draw(sf::RenderWindow& win) override;

    // [AGENT 4 ADDITION — updated applyEffect signature]
    void applyEffect(Paddle& lower, 
                     Paddle* upper, 
                     std::vector<Ball>& balls, 
                     float& effectTimer,
                     float windowWidth) override;

    std::string getType() const override;
};

#endif // GREENFOOD_H
