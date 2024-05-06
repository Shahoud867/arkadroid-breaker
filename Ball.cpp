#include "Ball.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <algorithm>

/**
 * @file Ball.cpp
 * @brief Implementation of the Ball class methods.
 */

Ball::Ball(float x, float y, float radius, float speed)
    : speed(speed), active(true), currentColor(sf::Color::White) {
    shape.setRadius(radius);
    
    // [NOTE: SFML CAVEAT — shape origin set to radius to make position represent the center]
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(currentColor);
    
    previousPosition = sf::Vector2f(x, y);
    
    // Initialize velocity to a standard upward-diagonal vector
    const float DIR_X = 0.7071f;
    const float DIR_Y = -0.7071f;
    velocity = sf::Vector2f(DIR_X, DIR_Y) * speed;
}

Ball::Ball(const Ball& other)
    : shape(other.shape),
      velocity(other.velocity),
      speed(other.speed),
      active(other.active),
      currentColor(other.currentColor),
      previousPosition(other.previousPosition) {}

void Ball::update(float dt) {
    previousPosition = shape.getPosition();
    shape.move(velocity * dt);
}

void Ball::draw(sf::RenderWindow& win) {
    win.draw(shape);
}

void Ball::reflectX() {
    velocity.x = -velocity.x;
}

void Ball::reflectY() {
    velocity.y = -velocity.y;
}

void Ball::setColor(sf::Color c) {
    currentColor = c;
    shape.setFillColor(currentColor);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::setVelocity(sf::Vector2f v) {
    velocity = v;
    speed = std::sqrt(v.x * v.x + v.y * v.y);
}

void Ball::multiplySpeed(float factor) {
    speed *= factor;
    float currentMag = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (currentMag > 0.f) {
        velocity = (velocity / currentMag) * speed;
    }
}

float Ball::getSpeed() const {
    return speed;
}

bool Ball::isActive() const {
    return active;
}

void Ball::setActive(bool a) {
    active = a;
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

void Ball::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
    previousPosition = pos;
}

Ball::HitSide Ball::detectCollisionSide(const sf::FloatRect& target) const {
    sf::FloatRect currentBounds = getBounds();
    if (!currentBounds.intersects(target)) {
        return HitSide::NONE;
    }

    float radius = shape.getRadius();
    sf::FloatRect prevBounds(sf::Vector2f(previousPosition.x - radius, previousPosition.y - radius), sf::Vector2f(radius * 2.f, radius * 2.f));

    bool prevOutsideLeft   = prevBounds.left + prevBounds.width <= target.left;
    bool prevOutsideRight  = prevBounds.left >= target.left + target.width;
    bool prevOutsideTop    = prevBounds.top + prevBounds.height <= target.top;
    bool prevOutsideBottom = prevBounds.top >= target.top + target.height;

    float overlapX = std::min(currentBounds.left + currentBounds.width, target.left + target.width) - std::max(currentBounds.left, target.left);
    float overlapY = std::min(currentBounds.top + currentBounds.height, target.top + target.height) - std::max(currentBounds.top, target.top);

    if (prevOutsideLeft && !prevOutsideTop && !prevOutsideBottom) {
        return HitSide::LEFT;
    }
    if (prevOutsideRight && !prevOutsideTop && !prevOutsideBottom) {
        return HitSide::RIGHT;
    }
    if (prevOutsideTop && !prevOutsideLeft && !prevOutsideRight) {
        return HitSide::TOP;
    }
    if (prevOutsideBottom && !prevOutsideLeft && !prevOutsideRight) {
        return HitSide::BOTTOM;
    }

    if (prevOutsideLeft || prevOutsideRight || prevOutsideTop || prevOutsideBottom) {
        if (overlapX < overlapY) {
            if (prevOutsideLeft) return HitSide::LEFT;
            if (prevOutsideRight) return HitSide::RIGHT;
        } else {
            if (prevOutsideTop) return HitSide::TOP;
            if (prevOutsideBottom) return HitSide::BOTTOM;
        }
    }

    if (overlapX < overlapY) {
        return (velocity.x > 0.f) ? HitSide::LEFT : HitSide::RIGHT;
    } else {
        return (velocity.y > 0.f) ? HitSide::TOP : HitSide::BOTTOM;
    }
}

void Ball::handleCollision(const sf::FloatRect& target) {
    HitSide side = detectCollisionSide(target);
    if (side == HitSide::NONE) {
        return;
    }

    sf::FloatRect currentBounds = getBounds();
    float radius = shape.getRadius();
    sf::FloatRect prevBounds(sf::Vector2f(previousPosition.x - radius, previousPosition.y - radius), sf::Vector2f(radius * 2.f, radius * 2.f));

    bool prevOutsideX = (prevBounds.left + prevBounds.width <= target.left) || 
                        (prevBounds.left >= target.left + target.width);
    bool prevOutsideY = (prevBounds.top + prevBounds.height <= target.top) || 
                        (prevBounds.top >= target.top + target.height);

    if (prevOutsideX && prevOutsideY) {
        float overlapX = std::min(currentBounds.left + currentBounds.width, target.left + target.width) - std::max(currentBounds.left, target.left);
        float overlapY = std::min(currentBounds.top + currentBounds.height, target.top + target.height) - std::max(currentBounds.top, target.top);
        
        const float CORNER_EPSILON = 2.0f;
        if (std::abs(overlapX - overlapY) < CORNER_EPSILON) {
            reflectX();
            reflectY();
            return;
        }
    }

    switch (side) {
        case HitSide::LEFT:
        case HitSide::RIGHT:
            reflectX();
            break;
        case HitSide::TOP:
        case HitSide::BOTTOM:
            reflectY();
            break;
        default:
            break;
    }
}