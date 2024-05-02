#ifndef REDBRICK_H
#define REDBRICK_H

#include "Brick.h"

namespace sf {
    class RenderWindow;
}
class Food;

/**
 * @file RedBrick.h
 * @brief Subclass representing a Red Brick (3 HP, Score = 30, drops Red Food).
 */
class RedBrick : public Brick {
public:
    RedBrick(float x, float y);
    RedBrick(const RedBrick& other);
    void takeDamage() override;
    Food* dropFood() override;
    void draw(sf::RenderWindow& win) override;
    int getScoreValue() const override;
};

#endif // REDBRICK_H
