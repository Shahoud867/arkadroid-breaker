#ifndef REDFOOD_H
#define REDFOOD_H

#include "Food.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file RedFood.h
 * @brief Subclass representing Red Food (Power-down: accelerates all active balls by 50%).
 */
class RedFood : public Food {
private:
    sf::RectangleShape shape; ///< Rectangle shape representing the food item

public:
    RedFood(float x, float y);
    void draw(sf::RenderWindow& win) override;

    // [AGENT 4 ADDITION — updated applyEffect signature]
    void applyEffect(Paddle& lower, 
                     Paddle* upper, 
                     std::vector<Ball>& balls, 
                     float& effectTimer,
                     float windowWidth) override;

    std::string getType() const override;
};

#endif // REDFOOD_H
