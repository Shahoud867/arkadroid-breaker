#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sf {
    class RenderWindow;
}

/**
 * @struct Particle
 * @brief Represents a single visual particle inside our particle engine.
 */
struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
    float maxLifetime;
};

/**
 * @class ParticleSystem
 * @brief Manages spawning, updating, and drawing high-tech neon visual particles.
 */
class ParticleSystem {
private:
    std::vector<Particle> particles;

public:
    ParticleSystem() = default;

    /**
     * @brief Spawn a circular explosion burst of glowing particles.
     * @param pos Launch coordinate.
     * @param color Base color of particles.
     * @param count Quantity to spawn.
     */
    void spawnBurst(sf::Vector2f pos, sf::Color color, int count = 15);

    /**
     * @brief Move and age active particles.
     * @param dt Elapsed seconds.
     */
    void update(float dt);

    /**
     * @brief Render all active particles with fading opacity.
     * @param win sf::RenderWindow to draw to.
     */
    void draw(sf::RenderWindow& win);

    /**
     * @brief Clear all active particles.
     */
    void clear();
};

#endif // PARTICLESYSTEM_H
