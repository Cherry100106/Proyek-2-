#include "nashwa.h"

int grid[GRID_HEIGHT][GRID_WIDTH] = {0};

void InitGrid() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = 0;
        }
    }
}

bool CheckCollision(Tetromino *tetromino, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        int newX = tetromino->blocks[i].x + dx;
        int newY = tetromino->blocks[i].y + dy;
        if (newX < 0 || newX >= GRID_WIDTH || newY >= GRID_HEIGHT || (newY >= 0 && grid[newY][newX])) {
            return true;
        }
    }
    return false;
}

void PlaceTetromino(Tetromino *tetromino) {
    for (int i = 0; i < 4; i++) {
        if (tetromino->blocks[i].y >= 0)
            grid[tetromino->blocks[i].y][tetromino->blocks[i].x] = 1;
    }
}

bool CheckGameOver() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        if (grid[0][x]) return true;
    }
    return false;
}

int ClearRows() {
    int score = 0;
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
        bool full = true;
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            score += 100;
            for (int ny = y; ny > 0; ny--) {
                for (int x = 0; x < GRID_WIDTH; x++) {
                    grid[ny][x] = grid[ny - 1][x];
                }
            }
            for (int x = 0; x < GRID_WIDTH; x++) {
                grid[0][x] = 0;
            }
            y++; 
        }
    }
    return score;