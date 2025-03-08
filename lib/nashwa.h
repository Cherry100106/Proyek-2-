#ifndef NASHWA_H
#define NASHWA_H

#include "raylib.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

typedef struct {
    int x, y;
    Color color;
} Block;

typedef struct {
    Block blocks[4];
} Tetromino;

extern int grid[GRID_HEIGHT][GRID_WIDTH];

void InitGrid();
bool CheckCollision(Tetromino *tetromino, int dx, int dy);
void PlaceTetromino(Tetromino *tetromino);
bool CheckGameOver();
int ClearRows();

#endif