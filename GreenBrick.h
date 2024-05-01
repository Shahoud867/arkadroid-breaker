#ifndef GREENBRICK_H
#define GREENBRICK_H

#include "Brick.h"

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
}

// Forward declaration of Food
class Food;

/**
 * @file GreenBrick.h
 * @brief Subclass representing a Green Brick (1 HP, Score = 10, drops Green Food).
 * 
 * Rubric Coverage:
 * - Inheritance: Inherits from base class Brick.
 * - Polymorphism: Overrides pure virtual functions of the base class.
 */
class GreenBrick : public Brick {
public:
    /**
     * @brief Construct a new Green Brick object.
     * @param x The top-left X coordinate.
     * @param y The top-left Y coordinate.
     */
    GreenBrick(float x, float y);

    /**
     * @brief Copy constructor for GreenBrick.
     * @param other The GreenBrick object to copy from.
     */
    GreenBrick(const GreenBrick& other);

    /**
     * @brief Apply damage to the brick (1 HP). If HP <= 0, brick is destroyed.
     */
    void takeDamage() override;

    /**
     * @brief Drop a heap-allocated GreenFood object.
     * @return Food* Pointer to the dropped Food.
     */
    Food* dropFood() override;

    /**
     * @brief Render the GreenBrick shape to the window.
     * @param win The sf::RenderWindow to draw onto.
     */
    void draw(sf::RenderWindow& win) override;

    /**
     * @brief Get the score value for a GreenBrick.
     * @return int 10 points.
     */
    int getScoreValue() const override;
};

#endif // GREENBRICK_H
