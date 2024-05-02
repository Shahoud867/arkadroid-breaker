#ifndef BLUEBRICK_H
#define BLUEBRICK_H

#include "Brick.h"

namespace sf {
    class RenderWindow;
}
class Food;

/**
 * @file BlueBrick.h
 * @brief Subclass representing a Blue Brick (3 HP, Score = 30, drops Blue Food).
 */
class BlueBrick : public Brick {
public:
    BlueBrick(float x, float y);
    BlueBrick(const BlueBrick& other);
    void takeDamage() override;
    Food* dropFood() override;
    void draw(sf::RenderWindow& win) override;
    int getScoreValue() const override;
};

#endif // BLUEBRICK_H
