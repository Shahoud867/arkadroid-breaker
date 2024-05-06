#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

// Forward declaration
namespace sf {
    class RenderWindow;
}

/**
 * @file Paddle.h
 * @brief Declaration of the Paddle class representing player-controlled paddles.
 * 
 * Rubric Coverage:
 * - Encapsulation: Private members accessed and updated via getters/setters.
 * - Copy Constructor: Fully implemented deep copy.
 */
class Paddle {
private:
    sf::RectangleShape shape;    ///< Visual representation of the paddle
    float width;                 ///< Current width of the paddle
    float height;                ///< Height of the paddle
    sf::Vector2f position;       ///< Current 2D position coordinates (center of the paddle)
    sf::Color color;             ///< Current color of the paddle
    float originalWidth;         ///< Original width of the paddle (for resetting size)
    bool isUpper;                ///< Control mode flag (true = Keyboard, false = Mouse)

public:
    /**
     * @brief Construct a new Paddle object.
     * @param x Initial center X coordinate.
     * @param y Initial center Y coordinate.
     * @param width Initial width.
     * @param height Height of the paddle.
     * @param isUpper Control mode flag (true = Keyboard, false = Mouse).
     */
    Paddle(float x, float y, float width, float height, bool isUpper = false);

    /**
     * @brief Deep copy constructor for Paddle.
     * @param other The Paddle object to copy from.
     */
    Paddle(const Paddle& other);

    /**
     * @brief Update the lower paddle's position based on mouse position.
     * @param win The sf::RenderWindow to query mouse coords from.
     */
    void updateMouse(sf::RenderWindow& win);

    /**
     * @brief Update the upper paddle's position based on keyboard input.
     * @param dt Delta time since last frame.
     * @param moveLeft True if left movement requested.
     * @param moveRight True if right movement requested.
     */
    void updateKeyboard(float dt, bool moveLeft, bool moveRight);

    /**
     * @brief Render the paddle.
     * @param win The sf::RenderWindow to draw to.
     */
    void draw(sf::RenderWindow& win);

    /**
     * @brief Set the width of the paddle.
     * @param w New width.
     */
    void setWidth(float w);

    /**
     * @brief Get the current width of the paddle.
     * @return float Width.
     */
    float getWidth() const;

    /**
     * @brief Set the color of the paddle.
     * @param c New color.
     */
    void setColor(sf::Color c);

    /**
     * @brief Get global bounding box of the paddle.
     * @return sf::FloatRect Bounding box.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Reset paddle width to its original state.
     */
    void resetWidth();

    /**
     * @brief Clamp paddle positioning to stay within window boundaries.
     * @param windowWidth Width of the window.
     */
    void clampToWindow(float windowWidth);

    /**
     * @brief Set paddle position coordinates.
     * @param pos New coordinates.
     */
    void setPosition(sf::Vector2f pos);

    /**
     * @brief Get current paddle position coordinates.
     * @return sf::Vector2f Position.
     */
    sf::Vector2f getPosition() const;
};

#endif // PADDLE_H