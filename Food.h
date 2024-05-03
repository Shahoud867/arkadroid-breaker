#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Forward declarations
namespace sf {
    class RenderWindow;
}
class Paddle;
class Ball;

/**
 * @file Food.h
 * @brief Base class representing Food (Power-ups/downs falling from destroyed bricks).
 * 
 * Rubric Coverage:
 * - Abstraction: Pure virtual draw, applyEffect, and getType functions.
 * - Inheritance: Subclasses representing different types of food.
 */
class Food {
protected:
    sf::Vector2f position;       ///< Current position coordinates
    float fallSpeed;             ///< Speed at which the food falls downwards
    bool active;                 ///< Flag indicating if food is active/on-screen
    bool collected;              ///< Flag indicating if food has been collected
    sf::FloatRect bounds;        ///< Bounding box for collision detection

public:
    /**
     * @brief Construct a new Food object.
     * @param x Initial X coordinate.
     * @param y Initial Y coordinate.
     * @param speed Speed of falling.
     * @param sz Size dimensions of the bounding box.
     */
    Food(float x, float y, float speed, sf::Vector2f sz);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Food() {}

    /**
     * @brief Update the food's position.
     * @param dt Delta time since last frame.
     */
    void update(float dt);

    /**
     * @brief Render the food shape. Pure virtual.
     * @param win The sf::RenderWindow to draw to.
     */
    virtual void draw(sf::RenderWindow& win) = 0;

    /**
     * @brief Apply food effect to gameplay state. Pure virtual.
     * @param lower Reference to the lower Paddle.
     * @param upper Pointer to the upper Paddle (Level 3 only).
     * @param balls Reference to the collection of Ball objects.
     * @param effectTimer Reference to the power-up duration timer.
     * @param windowWidth Width of the game window.
     */
    virtual void applyEffect(Paddle& lower, 
                             Paddle* upper,
                             std::vector<Ball>& balls, 
                             float& effectTimer,
                             float windowWidth) = 0;

    /**
     * @brief Get the string name representation of this food subclass. Pure virtual.
     * @return std::string Subclass identifier.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Get the FloatRect bounds of this food.
     * @return sf::FloatRect Bounding box.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Check if this food is active.
     * @return true If active.
     * @return false Otherwise.
     */
    bool isActive() const;

    /**
     * @brief Mark this food as collected (deactivates it).
     */
    void collect();
};

#endif // FOOD_H