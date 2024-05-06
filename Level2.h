#ifndef LEVEL2_H
#define LEVEL2_H

#include "Level.h"

/**
 * @file Level2.h
 * @brief Declaration of Level2 class representing the second level.
 * 
 * [RUBRIC: Level 2 Brick Layout +10pts — Staircase / descending pattern, speed scaling to 1.3x]
 */
class Level2 : public Level {
public:
    /**
     * @brief Construct a new Level2 object.
     * Sets ballSpeedMultiplier to 1.3f.
     */
    Level2();

    /**
     * @brief Generate the staircase pattern.
     * @param windowW Width of the window.
     * @param windowH Height of the window.
     */
    void generatePattern(float windowW, float windowH) override;

    /**
     * @brief Check if all bricks are destroyed.
     * @return true If complete.
     * @return false Otherwise.
     */
    bool isComplete() const override;
};

#endif // LEVEL2_H
