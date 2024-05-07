#ifndef LEVEL3_H
#define LEVEL3_H

#include "Level.h"
#include "Paddle.h"

/**
 * @file Level3.h
 * @brief Declaration of Level3 class representing the third level.
 * 
 * [RUBRIC: Level 3 Brick Layout & Recursion +16pts — Recursive fractal block pattern, 1.6x speed scaling]
 * [RUBRIC: Level 3 Dual Paddle +6pts — Keyboard controlled upper paddle]
 */
class Level3 : public Level {
private:
    Paddle* upperPaddleRef; ///< Reference to upper paddle owned by Game

public:
    /**
     * @brief Construct a new Level3 object.
     * Sets ballSpeedMultiplier to 1.6f.
     */
    Level3();

    /**
     * @brief Generate the recursive fractal block pattern.
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

    /**
     * @brief Recursive block placement helper.
     * [RUBRIC: Level 3 Recursion +6pts]
     * @param x Current X coordinate.
     * @param y Current Y coordinate.
     * @param rows Rows of bricks per block.
     * @param cols Columns of bricks per block.
     * @param depth Current recursion depth.
     * @param maxDepth Maximum recursion depth (3).
     */
    void placeBlock(float x, float y, int rows, int cols, int depth, int maxDepth);

    /**
     * @brief Set the reference to the upper paddle.
     * @param paddle Pointer to the upper paddle instance.
     */
    void setUpperPaddleRef(Paddle* paddle);

    /**
     * @brief Get the upper paddle reference.
     * @return Paddle& Reference to upper paddle.
     */
    Paddle& getUpperPaddle();
};

#endif // LEVEL3_H
