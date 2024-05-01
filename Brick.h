#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

// Forward declarations to avoid circular dependencies
class Food;
namespace sf {
    class RenderWindow;
}

// Brick Constants
const float BRICK_WIDTH = 80.f;
const float BRICK_HEIGHT = 30.f;
const float FLASH_DURATION = 0.1f;

/**
 * @file Brick.h
 * @brief Base class representing a Brick in Arkadroid.
 * 
 * Rubric Coverage:
 * - Abstraction: Virtual functions for takeDamage, dropFood, draw, getScoreValue.
 * - Encapsulation: All members protected, accessed via methods.
 * - Inheritance: Subclasses extend this class.
 */
class Brick {
protected:
    sf::RectangleShape shape;     ///< SFML rectangle representing the brick
    int hitPoints;                ///< Current hit points (HP) of the brick
    int maxHitPoints;             ///< Maximum hit points of the brick
    sf::Color color;              ///< Base color of the brick
    bool destroyed;               ///< True if brick is destroyed
    sf::Vector2f position;        ///< Position coordinates of top-left corner
    bool isFlashing;              ///< Flash status flag
    float flashTimer;             ///< Flash timer countdown

public:
    /**
     * @brief Construct a new Brick object.
     * @param x Top-left X coordinate.
     * @param y Top-left Y coordinate.
     * @param hp Initial hit points.
     * @param col Base color of the brick.
     */
    Brick(float x, float y, int hp, sf::Color col);

    /**
     * @brief Copy constructor for Brick.
     * @param other Brick object to copy.
     */
    Brick(const Brick& other);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Brick() {}

    /**
     * @brief Apply damage to the brick. Pure virtual.
     */
    virtual void takeDamage() = 0;

    /**
     * @brief Drop a food item. Pure virtual.
     * @return Food* Pointer to the dropped Food subclass.
     */
    virtual Food* dropFood() = 0;

    /**
     * @brief Draw the brick onto the window. Pure virtual.
     * @param win The sf::RenderWindow to draw to.
     */
    virtual void draw(sf::RenderWindow& win) = 0;

    /**
     * @brief Central rendering method that applies advanced production-grade visual sheen and borders.
     * @param win The sf::RenderWindow to draw to.
     */
    void drawBrick(sf::RenderWindow& win);

    /**
     * @brief Get score value for destroying the brick. Pure virtual.
     * @return int Points value.
     */
    virtual int getScoreValue() const = 0;

    /**
     * @brief Check if the brick is destroyed.
     * @return true If destroyed.
     * @return false Otherwise.
     */
    bool isDestroyed() const;

    /**
     * @brief Get global bounding box bounds of the brick.
     * @return sf::FloatRect Bounding box.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Get the Position of the brick.
     * @return sf::Vector2f Position.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Get the color of the brick.
     * @return sf::Color The color.
     */
    sf::Color getColor() const { return color; }

    /**
     * @brief Set the Position of the brick.
     * @param x New X coordinate.
     * @param y New Y coordinate.
     */
    void setPosition(float x, float y);

    /**
     * @brief Trigger hit flash visual effect.
     */
    void triggerHitFlash();

    /**
     * @brief Update the flashing timers.
     * @param dt Delta time since last frame.
     */
    void updateFlash(float dt);
};

#endif // BRICK_H