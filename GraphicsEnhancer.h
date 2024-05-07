#ifndef GRAPHICSENHANCER_H
#define GRAPHICSENHANCER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

/**
 * @class GraphicsEnhancer
 * @brief Provides production-grade visual effects including neon glows,
 *        shadows, and smooth animations.
 * 
 * [AGENT 6 ADDITION — Production-grade graphics enhancement]
 */
class GraphicsEnhancer {
private:
    struct GlowEffect {
        sf::Vector2f position;
        float radius;
        sf::Color color;
        float intensity;
        float lifetime;
        float maxLifetime;
    };

    std::vector<GlowEffect> glowEffects;

public:
    GraphicsEnhancer() = default;

    /**
     * @brief Add a neon glow effect at a position.
     * @param pos Center position of the glow.
     * @param radius Size of the glow effect.
     * @param color Color of the glow (typically neon).
     * @param duration How long the glow lasts (seconds).
     */
    void addGlowEffect(sf::Vector2f pos, float radius, sf::Color color, float duration);

    /**
     * @brief Update all active glow effects.
     * @param dt Delta time in seconds.
     */
    void update(float dt);

    /**
     * @brief Draw all active glow effects to the window.
     * @param win Target render window.
     */
    void draw(sf::RenderWindow& win);

    /**
     * @brief Draw a neon-glowing circle.
     * @param win Target window.
     * @param shape Circle shape to glow.
     * @param glowColor Color of the neon glow.
     * @param glowThickness How thick the glow halo is.
     */
    static void drawNeonGlow(sf::RenderWindow& win, const sf::CircleShape& shape,
                            sf::Color glowColor, float glowThickness);

    /**
     * @brief Draw a neon-glowing rectangle.
     * @param win Target window.
     * @param shape Rectangle to glow.
     * @param glowColor Color of the neon glow.
     * @param glowThickness How thick the glow halo is.
     */
    static void drawNeonGlow(sf::RenderWindow& win, const sf::RectangleShape& shape,
                            sf::Color glowColor, float glowThickness);

    /**
     * @brief Draw a drop shadow effect.
     * @param win Target window.
     * @param shape Shape to shadow.
     * @param shadowOffset How far the shadow is from the shape.
     * @param shadowColor Color of the shadow.
     */
    static void drawShadow(sf::RenderWindow& win, const sf::CircleShape& shape,
                          sf::Vector2f shadowOffset, sf::Color shadowColor);

    /**
     * @brief Clear all active glow effects.
     */
    void clear();
};

#endif // GRAPHICSENHANCER_H
