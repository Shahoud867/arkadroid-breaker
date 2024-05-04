#ifndef PINKFOOD_H
#define PINKFOOD_H

#include "Food.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file PinkFood.h
 * @brief Subclass representing Pink Food (Power-down: shrinks paddle width by half).
 */
class PinkFood : public Food {
private:
    sf::RectangleShape shape; ///< Rectangle shape representing the square

public:
    PinkFood(float x, float y);
    void draw(sf::RenderWindow& win) override;

    // [AGENT 4 ADDITION — updated applyEffect signature]
    void applyEffect(Paddle& lower, 
                     Paddle* upper, 
                     std::vector<Ball>& balls, 
                     float& effectTimer,
                     float windowWidth) override;

    std::string getType() const override;
};

#endif // PINKFOOD_H
