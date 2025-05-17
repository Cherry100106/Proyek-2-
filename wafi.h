#ifndef WAFI_H
#define WAFI_H

#include <raylib.h>

#define NUM_ROWS 20
#define NUM_COLS 10

typedef struct {
    int row;
    int column;
} Position;

typedef struct {
    int id;
    char blockType; // 'I', 'O', 'T', 'S', 'Z', 'J', 'L'
    Position cells[4][4]; // 4 rotasi, masing-masing dengan 4 posisi
    int cellSize;
    int rotationState;
    Texture2D texture;
    int row; // Posisi absolut baris
    int col; // Posisi absolut kolom
} Block;

typedef struct {
    int grid[NUM_ROWS][NUM_COLS];
    int cellSize;
    Texture2D blockTextures[7];
} Grid;

typedef struct {
    int row;
    int column;
} WallKickOffset;

void Position_Init(Position *pos, int row, int column);
void Block_Init(Block *block);
void Block_Draw(Block *block, int offsetX, int offsetY);
void Grid_Init(Grid *grid);
void Grid_Draw(Grid *grid, int offsetX, int offsetY);
void LoadGridTextures(Grid *grid);
WallKickOffset* getWallKickOffsets(char blockType, int rotationFrom, int rotationTo);
int IsValidPosition(Block *block, Grid *grid);

#endif