#include "Paddle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

/**
 * @file Paddle.cpp
 * @brief Implementation of the Paddle class methods.
 */

Paddle::Paddle(float x, float y, float width, float height, bool isUpper)
    : width(width), height(height), position(x, y), color(sf::Color::White), originalWidth(width), isUpper(isUpper) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    
    // [NOTE: SFML CAVEAT — paddle origin set to center to make positioning and drawing symmetric]
    shape.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
    shape.setPosition(position);
}

Paddle::Paddle(const Paddle& other)
    : shape(other.shape),
      width(other.width),
      height(other.height),
      position(other.position),
      color(other.color),
      originalWidth(other.originalWidth),
      isUpper(other.isUpper) {
    // Re-apply properties explicitly to ensure deep separation of shape assets
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
    shape.setPosition(position);
}

void Paddle::updateMouse(sf::RenderWindow& win) {
    if (!isUpper) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(win);
        // Translate screen coordinates to coordinate system of the view
        sf::Vector2f worldMouse = win.mapPixelToCoords(mousePos);
        position.x = worldMouse.x;
        shape.setPosition(position);
    }
}

void Paddle::updateKeyboard(float dt, bool moveLeft, bool moveRight) {
    if (isUpper) {
        // Constant keyboard paddle speed (pixels per second)
        const float KEYBOARD_SPEED = 600.f;
        
        if (moveLeft) {
            position.x -= KEYBOARD_SPEED * dt;
        }
        if (moveRight) {
            position.x += KEYBOARD_SPEED * dt;
        }
        shape.setPosition(position);
    }
}

void Paddle::draw(sf::RenderWindow& win) {
    shape.setPosition(position);
    win.draw(shape);
}

void Paddle::setWidth(float w) {
    width = w;
    shape.setSize(sf::Vector2f(width, height));
    // [NOTE: SFML CAVEAT — must recompute origin center whenever width is modified]
    shape.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
}

float Paddle::getWidth() const {
    return width;
}

void Paddle::setColor(sf::Color c) {
    color = c;
    shape.setFillColor(color);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::resetWidth() {
    setWidth(originalWidth);
}

void Paddle::clampToWindow(float windowWidth) {
    float halfWidth = width / 2.f;
    if (position.x - halfWidth < 0.f) {
        position.x = halfWidth;
    }
    if (position.x + halfWidth > windowWidth) {
        position.x = windowWidth - halfWidth;
    }
    shape.setPosition(position);
}

void Paddle::setPosition(sf::Vector2f pos) {
    position = pos;
    shape.setPosition(position);
}

sf::Vector2f Paddle::getPosition() const {
    return position;
}