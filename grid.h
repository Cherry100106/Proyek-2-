#ifndef GRID_H
#define GRID_H
#include <raylib.h>
#include "colors.h"
#define NUM_ROWS 20
#define NUM_COLS 10

typedef struct {
    int grid[NUM_ROWS][NUM_COLS];
    int cellSize;
    Color colors[8];
} Grid;

void Grid_Init(Grid *grid);
void Grid_Print(Grid *grid);
void Grid_Draw(Grid *grid);

#endif
