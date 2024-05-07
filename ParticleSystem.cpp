#include "ParticleSystem.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdlib>
#include <cmath>

void ParticleSystem::spawnBurst(sf::Vector2f pos, sf::Color color, int count) {
    for (int i = 0; i < count; ++i) {
        float angle = static_cast<float>(std::rand() % 360) * 3.14159f / 180.f;
        float speed = 50.f + static_cast<float>(std::rand() % 200);
        
        Particle p;
        p.position = pos;
        p.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        p.color = color;
        p.maxLifetime = 0.3f + static_cast<float>(std::rand() % 40) / 100.f;
        p.lifetime = p.maxLifetime;
        particles.push_back(p);
    }
}

void ParticleSystem::update(float dt) {
    for (auto it = particles.begin(); it != particles.end(); ) {
        it->lifetime -= dt;
        if (it->lifetime <= 0.f) {
            it = particles.erase(it);
        } else {
            // Apply air drag and move particles
            it->velocity *= (1.f - dt * 2.0f);
            it->position += it->velocity * dt;
            ++it;
        }
    }
}

void ParticleSystem::draw(sf::RenderWindow& win) {
    for (const auto& p : particles) {
        float ratio = p.lifetime / p.maxLifetime;
        sf::Color drawColor = p.color;
        // Fade out particle opacity over time
        drawColor.a = static_cast<uint8_t>(ratio * 255.f);
        
        // Render as a tiny glowing neon square
        sf::RectangleShape shape(sf::Vector2f(4.f, 4.f));
        shape.setOrigin(sf::Vector2f(2.f, 2.f));
        shape.setPosition(p.position);
        shape.setFillColor(drawColor);
        win.draw(shape);
    }
}

void ParticleSystem::clear() {
    particles.clear();
}
