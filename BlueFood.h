#ifndef BLUEFOOD_H
#define BLUEFOOD_H

#include "Food.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file BlueFood.h
 * @brief Subclass representing Blue Food (Power-up: slows all active balls down by 50%).
 */
class BlueFood : public Food {
private:
    sf::CircleShape shape; ///< Circle shape representing the food item

public:
    BlueFood(float x, float y);
    void draw(sf::RenderWindow& win) override;

    // [AGENT 4 ADDITION — updated applyEffect signature]
    void applyEffect(Paddle& lower, 
                     Paddle* upper, 
                     std::vector<Ball>& balls, 
                     float& effectTimer,
                     float windowWidth) override;

    std::string getType() const override;
};

#endif // BLUEFOOD_H
