#ifndef PINKBRICK_H
#define PINKBRICK_H

#include "Brick.h"

namespace sf {
    class RenderWindow;
}
class Food;

/**
 * @file PinkBrick.h
 * @brief Subclass representing a Pink Brick (2 HP, Score = 20, drops Pink Food).
 */
class PinkBrick : public Brick {
public:
    PinkBrick(float x, float y);
    PinkBrick(const PinkBrick& other);
    void takeDamage() override;
    Food* dropFood() override;
    void draw(sf::RenderWindow& win) override;
    int getScoreValue() const override;
};

#endif // PINKBRICK_H
