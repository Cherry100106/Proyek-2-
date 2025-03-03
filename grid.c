#include "grid.h"
#include <stdio.h>

void Grid_Init(Grid *grid) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            grid->grid[i][j] = 0;
        }
    }
    grid->cellSize = 30;
}

void Grid_Print(Grid *grid) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%d ", grid->grid[i][j]);
        }
        printf("\n");
    }
}

void Grid_Draw(Grid *grid) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            DrawRectangle(j * grid->cellSize, i * grid->cellSize, grid->cellSize, grid->cellSize, BLUE);
            DrawRectangleLines(j * grid->cellSize, i * grid->cellSize, grid->cellSize, grid->cellSize, DARKBLUE);
        }
    }
}
