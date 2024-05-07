#include "GraphicsEnhancer.h"
#include <cmath>

/**
 * @file GraphicsEnhancer.cpp
 * @brief Implementation of production-grade graphics enhancement effects.
 * [AGENT 6 ADDITION — Production-grade visual polish]
 */

void GraphicsEnhancer::addGlowEffect(sf::Vector2f pos, float radius, sf::Color color, float duration) {
    GlowEffect glow;
    glow.position = pos;
    glow.radius = radius;
    glow.color = color;
    glow.intensity = 1.0f;
    glow.lifetime = duration;
    glow.maxLifetime = duration;
    glowEffects.push_back(glow);
}

void GraphicsEnhancer::update(float dt) {
    for (auto it = glowEffects.begin(); it != glowEffects.end(); ) {
        it->lifetime -= dt;
        if (it->lifetime <= 0.f) {
            it = glowEffects.erase(it);
        } else {
            // Fade out the glow as it expires
            it->intensity = it->lifetime / it->maxLifetime;
            ++it;
        }
    }
}

void GraphicsEnhancer::draw(sf::RenderWindow& win) {
    for (const auto& glow : glowEffects) {
        // Draw multiple concentric circles with decreasing opacity for glow effect
        for (int layer = 0; layer < 3; ++layer) {
            float layerRadius = glow.radius + (layer * 15.f);
            sf::CircleShape glowCircle(layerRadius);
            glowCircle.setPosition(glow.position.x - layerRadius, glow.position.y - layerRadius);
            
            sf::Color glowColor = glow.color;
            glowColor.a = static_cast<uint8_t>(glow.intensity * (255 - layer * 50));
            glowCircle.setFillColor(glowColor);
            win.draw(glowCircle);
        }
    }
}

void GraphicsEnhancer::drawNeonGlow(sf::RenderWindow& win, const sf::CircleShape& shape,
                                   sf::Color glowColor, float glowThickness) {
    // [AGENT 6 ADDITION — Neon glow effect for circles]
    sf::CircleShape glowShape = shape;
    
    // Draw multiple layers with increasing radius and decreasing opacity
    for (float i = glowThickness; i > 0.f; i -= 1.f) {
        float radiusIncrease = i;
        glowShape.setRadius(shape.getRadius() + radiusIncrease);
        glowShape.setPosition(shape.getPosition().x - radiusIncrease, 
                              shape.getPosition().y - radiusIncrease);
        
        glowColor.a = static_cast<uint8_t>(200.f * (1.f - i / glowThickness));
        glowShape.setFillColor(glowColor);
        win.draw(glowShape);
    }
    
    // Draw the original shape on top
    win.draw(shape);
}

void GraphicsEnhancer::drawNeonGlow(sf::RenderWindow& win, const sf::RectangleShape& shape,
                                   sf::Color glowColor, float glowThickness) {
    // [AGENT 6 ADDITION — Neon glow effect for rectangles]
    sf::RectangleShape glowShape = shape;
    
    // Draw multiple layers with increasing size and decreasing opacity
    for (float i = glowThickness; i > 0.f; i -= 1.f) {
        glowShape.setSize(sf::Vector2f(shape.getSize().x + i * 2.f, 
                                       shape.getSize().y + i * 2.f));
        glowShape.setPosition(shape.getPosition().x - i, shape.getPosition().y - i);
        
        glowColor.a = static_cast<uint8_t>(200.f * (1.f - i / glowThickness));
        glowShape.setFillColor(glowColor);
        win.draw(glowShape);
    }
    
    // Draw the original shape on top
    win.draw(shape);
}

void GraphicsEnhancer::drawShadow(sf::RenderWindow& win, const sf::CircleShape& shape,
                                 sf::Vector2f shadowOffset, sf::Color shadowColor) {
    // [AGENT 6 ADDITION — Drop shadow effect for depth]
    sf::CircleShape shadowShape = shape;
    shadowShape.setPosition(shape.getPosition() + shadowOffset);
    shadowColor.a = 100;  // Semi-transparent
    shadowShape.setFillColor(shadowColor);
    win.draw(shadowShape);
}

void GraphicsEnhancer::clear() {
    glowEffects.clear();
}
