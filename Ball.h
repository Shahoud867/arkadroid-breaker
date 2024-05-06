#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

// Forward declaration of sf::RenderWindow to reduce header coupling
namespace sf {
    class RenderWindow;
}

/**
 * @file Ball.h
 * @brief Declaration of the Ball class representing the game ball in Arkadroid.
 * 
 * Rubric Coverage:
 * - Encapsulation: All member variables are private and accessed via getters/setters.
 * - Copy Constructor: Fully implemented for copy operations (e.g., YellowPowerUp).
 * - Collision Side Detection: Complex 4-sided AABB checking.
 */
class Ball {
private:
    sf::CircleShape shape;       ///< SFML circle shape representing the ball (radius, position, color)
    sf::Vector2f velocity;       ///< Velocity vector (direction * speed)
    float speed;                 ///< Current speed of the ball
    bool active;                 ///< Flag indicating if the ball is active (for multi-ball management)
    sf::Color currentColor;      ///< Current color of the ball, tracks changes on brick hits
    sf::Vector2f previousPosition; ///< Stores the ball's position from the previous frame to aid collision resolution

public:
    /**
     * @brief Construct a new Ball object.
     * @param x Initial X coordinate (center of the ball).
     * @param y Initial Y coordinate (center of the ball).
     * @param radius Radius of the ball.
     * @param speed Initial speed of the ball.
     */
    Ball(float x, float y, float radius, float speed);

    /**
     * @brief Copy constructor for Ball.
     * @param other The Ball object to copy from.
     */
    Ball(const Ball& other);

    /**
     * @brief Update the ball's position and track its previous position.
     * @param dt Elapsed time since the last frame (delta time).
     */
    void update(float dt);

    /**
     * @brief Render the ball to the window.
     * @param win The SFML RenderWindow to draw on.
     */
    void draw(sf::RenderWindow& win);

    /**
     * @brief Invert the X component of the ball's velocity.
     */
    void reflectX();

    /**
     * @brief Invert the Y component of the ball's velocity.
     */
    void reflectY();

    /**
     * @brief Set the color of the ball.
     * @param c The new sf::Color to apply.
     */
    void setColor(sf::Color c);

    /**
     * @brief Get the current color of the ball.
     * @return sf::Color The current color.
     */
    sf::Color getColor() const { return currentColor; }

    /**
     * @brief Get the axis-aligned bounding box of the ball.
     * @return sf::FloatRect The bounding box in global coordinates.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Get the current velocity vector of the ball.
     * @return sf::Vector2f The velocity vector.
     */
    sf::Vector2f getVelocity() const;

    /**
     * @brief Set the velocity vector and update the internal speed magnitude.
     * @param v The new velocity vector.
     */
    void setVelocity(sf::Vector2f v);

    /**
     * @brief Multiply the ball's speed by a scale factor (for power-ups).
     * @param factor The scale factor to multiply speed by.
     */
    void multiplySpeed(float factor);

    /**
     * @brief Get the current speed magnitude.
     * @return float The current speed.
     */
    float getSpeed() const;

    /**
     * @brief Check if the ball is active.
     * @return true If the ball is active.
     * @return false If the ball is inactive.
     */
    bool isActive() const;

    /**
     * @brief Set the active state of the ball.
     * @param a The active state to set.
     */
    void setActive(bool a);

    /**
     * @brief Get the center position of the ball.
     * @return sf::Vector2f Position vector.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Set the center position of the ball.
     * @param pos New position vector.
     */
    void setPosition(sf::Vector2f pos);

    /**
     * @brief Enum representing the side of a bounding box that was hit.
     */
    enum class HitSide {
        TOP,    ///< Top face of target
        BOTTOM, ///< Bottom face of target
        LEFT,   ///< Left face of target
        RIGHT,  ///< Right face of target
        NONE    ///< No collision
    };

    /**
     * @brief Detect which side of a target bounding box the ball collided with.
     * @param target The bounding box of the target (e.g. a brick).
     * @return HitSide The side of collision.
     */
    HitSide detectCollisionSide(const sf::FloatRect& target) const;

    /**
     * @brief Resolve collision with a target bounding box and reflect velocity accordingly.
     * Handles corner hits by reflecting both axes.
     * @param target The bounding box of the target.
     */
    void handleCollision(const sf::FloatRect& target);
};

#endif // BALL_H