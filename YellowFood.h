#ifndef YELLOWFOOD_H
#define YELLOWFOOD_H

#include "Food.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file YellowFood.h
 * @brief Subclass representing Yellow Food (Power-up: triggers multi-ball mode, spawning 2 new balls).
 */
class YellowFood : public Food {
private:
    sf::RectangleShape shape; ///< Rectangle shape representing the square

public:
    YellowFood(float x, float y);
    void draw(sf::RenderWindow& win) override;

    // [AGENT 4 ADDITION — updated applyEffect signature]
    void applyEffect(Paddle& lower, 
                     Paddle* upper, 
                     std::vector<Ball>& balls, 
                     float& effectTimer,
                     float windowWidth) override;

    std::string getType() const override;
};

#endif // YELLOWFOOD_H
