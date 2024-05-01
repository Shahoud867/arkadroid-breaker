#include "Brick.h"
#include <algorithm>

/**
 * @file Brick.cpp
 * @brief Implementation of concrete Brick methods.
 */

Brick::Brick(float x, float y, int hp, sf::Color col)
    : hitPoints(hp), maxHitPoints(hp), color(col), destroyed(false), position(x, y), isFlashing(false), flashTimer(0.f) {
    shape.setSize(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT));
    shape.setPosition(position);
    shape.setFillColor(col);
}

Brick::Brick(const Brick& other)
    : shape(other.shape),
      hitPoints(other.hitPoints),
      maxHitPoints(other.maxHitPoints),
      color(other.color),
      destroyed(other.destroyed),
      position(other.position),
      isFlashing(other.isFlashing),
      flashTimer(other.flashTimer) {}

bool Brick::isDestroyed() const {
    return destroyed;
}

sf::FloatRect Brick::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Brick::getPosition() const {
    return position;
}

void Brick::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    shape.setPosition(position);
}

void Brick::triggerHitFlash() {
    isFlashing = true;
    flashTimer = FLASH_DURATION;
    
    // Lighten the color temporarily by adding value to each channel (clamp at 255)
    const int COLOR_OFFSET = 80;
    sf::Color flashColor(
        std::min(static_cast<int>(color.r) + COLOR_OFFSET, 255),
        std::min(static_cast<int>(color.g) + COLOR_OFFSET, 255),
        std::min(static_cast<int>(color.b) + COLOR_OFFSET, 255)
    );
    shape.setFillColor(flashColor);
}

void Brick::updateFlash(float dt) {
    if (isFlashing) {
        flashTimer -= dt;
        if (flashTimer <= 0.f) {
            isFlashing = false;
            shape.setFillColor(color); // Revert back to original base color
        }
    }
}

void Brick::drawBrick(sf::RenderWindow& win) {
    if (destroyed) return;
    
    // Draw the main base shape (solid or flashed color)
    win.draw(shape);
    
    // Draw a subtle 3D glossy reflection overlay on the top half for glass effect
    sf::RectangleShape gloss(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT / 2.f));
    gloss.setPosition(position);
    gloss.setFillColor(sf::Color(255, 255, 255, 45)); // White glossy sheen
    win.draw(gloss);
    
    // Draw an inner glowing border highlight for high-tech look
    sf::RectangleShape innerBorder(sf::Vector2f(BRICK_WIDTH - 2.f, BRICK_HEIGHT - 2.f));
    innerBorder.setPosition(sf::Vector2f(position.x + 1.f, position.y + 1.f));
    innerBorder.setFillColor(sf::Color::Transparent);
    
    sf::Color borderCol = isFlashing ? sf::Color::White : color;
    // Brighten the border color slightly for neon glow
    int borderR = std::min(static_cast<int>(borderCol.r) + 50, 255);
    int borderG = std::min(static_cast<int>(borderCol.g) + 50, 255);
    int borderB = std::min(static_cast<int>(borderCol.b) + 50, 255);
    
    innerBorder.setOutlineThickness(1.f);
    innerBorder.setOutlineColor(sf::Color(borderR, borderG, borderB, 180));
    win.draw(innerBorder);
}
