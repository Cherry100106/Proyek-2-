#include "wafi.h"
#include <stdlib.h> 
#include <time.h>   

void Position_Init(Position *pos, int row, int column) {
    pos->row = row;
    pos->column = column;
}

void Block_Init(Block *block) {
    block->id = rand() % 7; 
    block->cellSize = 30;
    block->rotationState = 0;

    // Warna blok
    block->colors[0] = RED;    // I
    block->colors[1] = ORANGE; // L
    block->colors[2] = YELLOW; // O
    block->colors[3] = GREEN;  // S
    block->colors[4] = BLUE;   // J
    block->colors[5] = PURPLE; // T
    block->colors[6] = PINK;   // Z

    // Inisialisasi bentuk blok berdasarkan ID
    switch (block->id) {
        case 0: // I
            // Rotasi 0° (horizontal)
            Position_Init(&block->cells[0][0], 0, 0);
            Position_Init(&block->cells[0][1], 0, 1);
            Position_Init(&block->cells[0][2], 0, 2);
            Position_Init(&block->cells[0][3], 0, 3);
            break;

        case 1: // L
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 0);
            Position_Init(&block->cells[0][1], 1, 0);
            Position_Init(&block->cells[0][2], 2, 0);
            Position_Init(&block->cells[0][3], 2, 1);
            // Rotasi 90°
            Position_Init(&block->cells[1][0], 1, 0);
            Position_Init(&block->cells[1][1], 1, 1);
            Position_Init(&block->cells[1][2], 1, 2);
            Position_Init(&block->cells[1][3], 0, 2);
            // Rotasi 180°
            Position_Init(&block->cells[2][0], 0, 0);
            Position_Init(&block->cells[2][1], 0, 1);
            Position_Init(&block->cells[2][2], 1, 1);
            Position_Init(&block->cells[2][3], 2, 1);
            // Rotasi 270°
            Position_Init(&block->cells[3][0], 0, 0);
            Position_Init(&block->cells[3][1], 0, 1);
            Position_Init(&block->cells[3][2], 0, 2);
            Position_Init(&block->cells[3][3], 1, 0);
            break;

        case 2: // J
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 1);
            Position_Init(&block->cells[0][1], 1, 1);
            Position_Init(&block->cells[0][2], 2, 1);
            Position_Init(&block->cells[0][3], 2, 0);
            // Rotasi 90°
            Position_Init(&block->cells[1][0], 1, 0);
            Position_Init(&block->cells[1][1], 1, 1);
            Position_Init(&block->cells[1][2], 1, 2);
            Position_Init(&block->cells[1][3], 2, 2);
            // Rotasi 180°
            Position_Init(&block->cells[2][0], 0, 1);
            Position_Init(&block->cells[2][1], 0, 2);
            Position_Init(&block->cells[2][2], 1, 1);
            Position_Init(&block->cells[2][3], 2, 1);
            // Rotasi 270°
            Position_Init(&block->cells[3][0], 0, 0);
            Position_Init(&block->cells[3][1], 1, 0);
            Position_Init(&block->cells[3][2], 1, 1);
            Position_Init(&block->cells[3][3], 1, 2);
            break;

        case 3: // O
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 0);
            Position_Init(&block->cells[0][1], 0, 1);
            Position_Init(&block->cells[0][2], 1, 0);
            Position_Init(&block->cells[0][3], 1, 1);
            // Rotasi 90° (sama dengan 0°)
            Position_Init(&block->cells[1][0], 0, 0);
            Position_Init(&block->cells[1][1], 0, 1);
            Position_Init(&block->cells[1][2], 1, 0);
            Position_Init(&block->cells[1][3], 1, 1);
            // Rotasi 180° (sama dengan 0°)
            Position_Init(&block->cells[2][0], 0, 0);
            Position_Init(&block->cells[2][1], 0, 1);
            Position_Init(&block->cells[2][2], 1, 0);
            Position_Init(&block->cells[2][3], 1, 1);
            // Rotasi 270° (sama dengan 0°)
            Position_Init(&block->cells[3][0], 0, 0);
            Position_Init(&block->cells[3][1], 0, 1);
            Position_Init(&block->cells[3][2], 1, 0);
            Position_Init(&block->cells[3][3], 1, 1);
            break;

        case 4: // S
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 1);
            Position_Init(&block->cells[0][1], 0, 2);
            Position_Init(&block->cells[0][2], 1, 0);
            Position_Init(&block->cells[0][3], 1, 1);
            // Rotasi 90°
            Position_Init(&block->cells[1][0], 0, 1);
            Position_Init(&block->cells[1][1], 1, 1);
            Position_Init(&block->cells[1][2], 1, 2);
            Position_Init(&block->cells[1][3], 2, 2);
            // Rotasi 180°
            Position_Init(&block->cells[2][0], 1, 1);
            Position_Init(&block->cells[2][1], 1, 2);
            Position_Init(&block->cells[2][2], 2, 0);
            Position_Init(&block->cells[2][3], 2, 1);
            // Rotasi 270°
            Position_Init(&block->cells[3][0], 0, 0);
            Position_Init(&block->cells[3][1], 1, 0);
            Position_Init(&block->cells[3][2], 1, 1);
            Position_Init(&block->cells[3][3], 2, 1);
            break;

        case 5: // T
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 1);
            Position_Init(&block->cells[0][1], 1, 0);
            Position_Init(&block->cells[0][2], 1, 1);
            Position_Init(&block->cells[0][3], 1, 2);
            // Rotasi 90°
            Position_Init(&block->cells[1][0], 0, 1);
            Position_Init(&block->cells[1][1], 1, 1);
            Position_Init(&block->cells[1][2], 1, 2);
            Position_Init(&block->cells[1][3], 2, 1);
            // Rotasi 180°
            Position_Init(&block->cells[2][0], 1, 0);
            Position_Init(&block->cells[2][1], 1, 1);
            Position_Init(&block->cells[2][2], 1, 2);
            Position_Init(&block->cells[2][3], 2, 1);
            // Rotasi 270°
            Position_Init(&block->cells[3][0], 0, 1);
            Position_Init(&block->cells[3][1], 1, 0);
            Position_Init(&block->cells[3][2], 1, 1);
            Position_Init(&block->cells[3][3], 2, 1);
            break;

        case 6: // Z
            // Rotasi 0°
            Position_Init(&block->cells[0][0], 0, 0);
            Position_Init(&block->cells[0][1], 0, 1);
            Position_Init(&block->cells[0][2], 1, 1);
            Position_Init(&block->cells[0][3], 1, 2);
            // Rotasi 90°
            Position_Init(&block->cells[1][0], 0, 2);
            Position_Init(&block->cells[1][1], 1, 1);
            Position_Init(&block->cells[1][2], 1, 2);
            Position_Init(&block->cells[1][3], 2, 1);
            // Rotasi 180°
            Position_Init(&block->cells[2][0], 1, 0);
            Position_Init(&block->cells[2][1], 1, 1);
            Position_Init(&block->cells[2][2], 2, 1);
            Position_Init(&block->cells[2][3], 2, 2);
            // Rotasi 270°
            Position_Init(&block->cells[3][0], 0, 1);
            Position_Init(&block->cells[3][1], 1, 0);
            Position_Init(&block->cells[3][2], 1, 1);
            Position_Init(&block->cells[3][3], 2, 0);
            break;
    }
}

void Block_Draw(Block *block, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row;
        int col = block->cells[block->rotationState][i].column;

        DrawRectangle(
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            block->cellSize, block->cellSize,
            block->colors[block->id % 7]
        );

        DrawRectangleLines(
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            block->cellSize, block->cellSize,
            BLACK
        );
    }
}

void Grid_Init(Grid *grid) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            grid->grid[i][j] = 0;
        }
    }
    grid->cellSize = 30;
}

void Grid_Draw(Grid *grid,int offsetX,int offsetY) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (grid->grid[i][j]) {
                DrawRectangle(
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    grid->cellSize, grid->cellSize,
                    BLUE
                );
                DrawRectangleLines(
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    grid->cellSize, grid->cellSize,
                    DARKBLUE
                );
            } else {
                // Gambar grid kosong
                DrawRectangleLines(
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    grid->cellSize, grid->cellSize,
                    LIGHTGRAY
                );
            }
        }
    }
}