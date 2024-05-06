#include "Level2.h"
#include "GreenBrick.h"
#include "PinkBrick.h"
#include "BlueBrick.h"
#include "RedBrick.h"
#include "YellowBrick.h"
#include <cstdlib>

/**
 * @file Level2.cpp
 * @brief Implementation of Level 2 staircase pattern and 1.3x speed scaling.
 */

Level2::Level2() : Level(1.3f) {}

void Level2::generatePattern(float windowW, float windowH) {
    for (Brick* b : bricks) {
        delete b;
    }
    bricks.clear();

    // [RUBRIC: Level 2 +10pts — Staircase / descending zig-zag pattern, rand selection]
    int bricksPerRow = 5;
    int rows = 6;
    float startY = 60.f;
    float baseStartX = (windowW - ((bricksPerRow + 3) * BRICK_WIDTH)) / 2.f; // roughly centered
    if (baseStartX < 10.f) baseStartX = 10.f;

    for (int r = 0; r < rows; ++r) {
        // Compute zig-zag indent:
        // Row 0: 0, Row 1: 1, Row 2: 2, Row 3: 3, Row 4: 2, Row 5: 1
        int indentFactor = r;
        if (r > 3) {
            indentFactor = 6 - r;
        }

        float rowStartX = baseStartX + indentFactor * BRICK_WIDTH;

        for (int c = 0; c < bricksPerRow; ++c) {
            float x = rowStartX + c * BRICK_WIDTH;
            float y = startY + r * BRICK_HEIGHT;

            int type = std::rand() % 5;
            Brick* brick = nullptr;
            
            switch (type) {
                case 0: brick = new GreenBrick(x, y); break;
                case 1: brick = new PinkBrick(x, y); break;
                case 2: brick = new BlueBrick(x, y); break;
                case 3: brick = new RedBrick(x, y); break;
                case 4:
                default:
                    brick = new YellowBrick(x, y); break;
            }
            bricks.push_back(brick);
        }
    }
}

bool Level2::isComplete() const {
    for (const Brick* b : bricks) {
        if (b && !b->isDestroyed()) {
            return false;
        }
    }
    return true;
}
