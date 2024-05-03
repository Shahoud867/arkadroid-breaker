#include "Food.h"

/**
 * @file Food.cpp
 * @brief Implementation of concrete Food methods.
 */

Food::Food(float x, float y, float speed, sf::Vector2f sz)
    : position(x, y), fallSpeed(speed), active(true), collected(false) {
    // Setup initial bounding box centered around the (x, y) origin
    bounds = sf::FloatRect(x - sz.x / 2.f, y - sz.y / 2.f, sz.x, sz.y);
}

void Food::update(float dt) {
    // Move downward by velocity * dt
    position.y += fallSpeed * dt;
    
    // Update the AABB bounds to keep in sync with the current position
    bounds = sf::FloatRect(position.x - bounds.width / 2.f, position.y - bounds.height / 2.f, bounds.width, bounds.height);
}

sf::FloatRect Food::getBounds() const {
    return bounds;
}

bool Food::isActive() const {
    return active;
}

void Food::collect() {
    collected = true;
    active = false;
}
