#ifndef LEVEL1_H
#define LEVEL1_H

#include "Level.h"

/**
 * @file Level1.h
 * @brief Declaration of Level1 class representing the first level.
 * 
 * [RUBRIC: Level 1 Brick Layout +10pts — Solid rectangle grid, random brick types, isComplete checks]
 */
class Level1 : public Level {
public:
    /**
     * @brief Construct a new Level1 object.
     * Sets ballSpeedMultiplier to 1.0f.
     */
    Level1();

    /**
     * @brief Generate a solid rectangle grid layout.
     * @param windowW Width of the window.
     * @param windowH Height of the window.
     */
    void generatePattern(float windowW, float windowH) override;

    /**
     * @brief Check if all bricks are destroyed.
     * @return true If all bricks are destroyed.
     * @return false Otherwise.
     */
    bool isComplete() const override;
};

#endif // LEVEL1_H
