#include "nashwa.h"

bool CheckCollision(Block *block, Grid *grid, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        int newRow = block->cells[block->rotationState][i].row + dy;
        int newCol = block->cells[block->rotationState][i].column + dx;
        if (newCol < 0 || newCol >= NUM_COLS || newRow >= NUM_ROWS || (newRow >= 0 && grid->grid[newRow][newCol])) {
            return true;
        }
    }
    return false;
}

void PlaceTetromino(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row;
        int col = block->cells[block->rotationState][i].column;
        if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
            grid->grid[row][col] = block->id + 1; // Simpan ID blok ke grid
        }
    }
}

bool CheckGameOver(Grid *grid) {
    for (int col = 0; col < NUM_COLS; col++) {
        if (grid->grid[0][col]) return true;
    }
    return false;
}

int ClearRows(Grid *grid) {
    int score = 0;
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        bool full = true;
        for (int col = 0; col < NUM_COLS; col++) {
            if (grid->grid[row][col] == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            score += 100;
            for (int r = row; r > 0; r--) {
                for (int col = 0; col < NUM_COLS; col++) {
                    grid->grid[r][col] = grid->grid[r - 1][col];
                }
            }
            for (int col = 0; col < NUM_COLS; col++) {
                grid->grid[0][col] = 0;
            }
            row++;
        }
    }
    return score;
}