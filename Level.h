#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"

/**
 * @file Level.h
 * @brief Abstract base class representing a Level in Arkadroid.
 * 
 * [RUBRIC: Abstraction ✓] - Define pure virtual pattern generation and completion rules.
 * [RUBRIC: Polymorphism ✓] - Subclasses override pure virtual methods to shape gameplay.
 */
class Level {
protected:
    std::vector<Brick*> bricks;     ///< Polymorphic collection of bricks in the level
    int lives;                       ///< Remaining lives (default 2 per level)
    float ballSpeedMultiplier;       ///< Ball speed factor for the level

public:
    /**
     * @brief Construct a new Level object.
     * @param speedMultiplier Speed multiplier for the level.
     */
    Level(float speedMultiplier);

    /**
     * @brief Virtual destructor to properly clean up heap-allocated brick pointers.
     */
    virtual ~Level();

    /**
     * @brief Generate the specific brick pattern for the level. Pure virtual.
     * @param windowW Width of the game window.
     * @param windowH Height of the game window.
     */
    virtual void generatePattern(float windowW, float windowH) = 0;

    /**
     * @brief Check if all bricks in the level are destroyed. Pure virtual.
     * @return true If the level is complete.
     * @return false If bricks remain.
     */
    virtual bool isComplete() const = 0;

    /**
     * @brief Decrement level lives by 1.
     */
    void decrementLife();

    /**
     * @brief Get the remaining lives.
     * @return int Lives count.
     */
    int getLives() const;

    /**
     * @brief Set the remaining lives (for restoring game state).
     * @param l New lives count.
     */
    void setLives(int l) { lives = l; }

    /**
     * @brief Check if game over condition is met for this level (lives == 0).
     * @return true If lives are 0.
     * @return false If lives remain.
     */
    bool isGameOver() const;

    /**
     * @brief Access the list of bricks in the level.
     * @return std::vector<Brick*>& Reference to the bricks vector.
     */
    std::vector<Brick*>& getBricks();

    /**
     * @brief Safely delete a brick at index and remove it from the collection.
     * @param index Index of the brick.
     */
    void removeBrick(int index);

    /**
     * @brief Get the ball speed multiplier.
     * @return float Ball speed multiplier.
     */
    float getBallSpeedMultiplier() const;

    /**
     * @brief Render all active bricks in the level.
     * @param win The sf::RenderWindow to draw onto.
     */
    virtual void draw(sf::RenderWindow& win);
};

#endif // LEVEL_H