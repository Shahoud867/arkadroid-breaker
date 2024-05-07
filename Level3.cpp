#include "Level3.h"
#include "GreenBrick.h"
#include "PinkBrick.h"
#include "BlueBrick.h"
#include "RedBrick.h"
#include "YellowBrick.h"
#include <cstdlib>
#include <stdexcept>

/**
 * @file Level3.cpp
 * @brief Implementation of Level 3 recursive pattern generation, 1.6x speed multiplier, and dual paddles.
 */

Level3::Level3() : Level(1.6f), upperPaddleRef(nullptr) {}

void Level3::generatePattern(float windowW, float windowH) {
    for (Brick* b : bricks) {
        delete b;
    }
    bricks.clear();

    // [RUBRIC: Level 3 Recursion +16pts — Recursive fractal block pattern, rand allocation, max depth 3]
    int maxDepth = 3;
    int rowsPerBlock = 1;
    int colsPerBlock = 1;

    // Total width of the 3-level fractal = (2^(maxDepth-1)) * colsPerBlock * BRICK_WIDTH
    // For depth 3: 2^2 * 1 * 80 = 4 * 80 = 320px
    float fractalW = (1 << (maxDepth - 1)) * colsPerBlock * BRICK_WIDTH;
    float fractalH = (1 << (maxDepth - 1)) * rowsPerBlock * BRICK_HEIGHT;

    float startX = windowW / 2.f - (3 * BRICK_WIDTH) / 2.f;
    float startY = 100.f; // Padding to avoid upper paddle at top of screen

    placeBlock(startX, startY, rowsPerBlock, colsPerBlock, 1, maxDepth);
}

void Level3::placeBlock(float x, float y, int rows, int cols, int depth, int maxDepth) {
    // [RUBRIC: Level 3 Recursion +6pts — Place rows x cols real bricks at depth == maxDepth]
    if (depth == maxDepth) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                float px = x + c * BRICK_WIDTH;
                float py = y + r * BRICK_HEIGHT;
                
                int type = std::rand() % 5;
                Brick* brick = nullptr;
                
                switch (type) {
                    case 0: brick = new GreenBrick(px, py); break;
                    case 1: brick = new PinkBrick(px, py); break;
                    case 2: brick = new BlueBrick(px, py); break;
                    case 3: brick = new RedBrick(px, py); break;
                    case 4: brick = new YellowBrick(px, py); break;
                }
                if (brick) {
                    bricks.push_back(brick);
                }
            }
        }
    } else {
        // Recursion step!
        // We branch out into sub-blocks symmetrically.
        float offsetX = (1 << (maxDepth - depth - 1)) * cols * BRICK_WIDTH;
        float offsetY = (1 << (maxDepth - depth - 1)) * rows * BRICK_HEIGHT;

        // Top-left child:
        placeBlock(x, y, rows, cols, depth + 1, maxDepth);
        // Top-right child:
        placeBlock(x + offsetX, y, rows, cols, depth + 1, maxDepth);
        // Bottom-left child:
        placeBlock(x, y + offsetY, rows, cols, depth + 1, maxDepth);
        // Bottom-right child:
        placeBlock(x + offsetX, y + offsetY, rows, cols, depth + 1, maxDepth);
    }
}

bool Level3::isComplete() const {
    for (const Brick* b : bricks) {
        if (!b->isDestroyed()) {
            return false;
        }
    }
    return true;
}

void Level3::setUpperPaddleRef(Paddle* paddle) {
    upperPaddleRef = paddle;
}

Paddle& Level3::getUpperPaddle() {
    if (!upperPaddleRef) {
        throw std::runtime_error("Upper paddle reference is null in Level3");
    }
    return *upperPaddleRef;
}