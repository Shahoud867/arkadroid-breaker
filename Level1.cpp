#include "Level1.h"
#include "GreenBrick.h"
#include "PinkBrick.h"
#include "BlueBrick.h"
#include "RedBrick.h"
#include "YellowBrick.h"
#include <cstdlib>

/**
 * @file Level1.cpp
 * @brief Implementation of Level 1 pattern generation.
 */

Level1::Level1() : Level(1.0f) {}

void Level1::generatePattern(float windowW, float windowH) {
    // Clean up existing bricks if any
    for (Brick* b : bricks) {
        delete b;
    }
    bricks.clear();

    // [RUBRIC: Level 1 +10pts — Solid rectangle grid of random bricks]
    int cols = 8;
    int rows = 4;
    float startX = (windowW - (cols * BRICK_WIDTH)) / 2.f;
    float startY = 60.f;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float x = startX + c * BRICK_WIDTH;
            float y = startY + r * BRICK_HEIGHT;
            
            // Randomly allocate brick type (0-4)
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

bool Level1::isComplete() const {
    // Level is complete when all bricks are marked destroyed
    for (const Brick* b : bricks) {
        if (b && !b->isDestroyed()) {
            return false;
        }
    }
    return true;
}
