#ifndef YELLOWBRICK_H
#define YELLOWBRICK_H

#include "Brick.h"

namespace sf {
    class RenderWindow;
}
class Food;

/**
 * @file YellowBrick.h
 * @brief Subclass representing a Yellow Brick (2 HP, Score = 20, drops Yellow Food).
 */
class YellowBrick : public Brick {
public:
    YellowBrick(float x, float y);
    YellowBrick(const YellowBrick& other);
    void takeDamage() override;
    Food* dropFood() override;
    void draw(sf::RenderWindow& win) override;
    int getScoreValue() const override;
};

#endif // YELLOWBRICK_H
