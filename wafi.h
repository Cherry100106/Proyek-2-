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

typedef struct GridNode {
    int row;
    int col;
    int blockId; // 0 untuk kosong, >0 untuk ID tetromino (+1 dari Block.id)
    struct GridNode* next;
    struct GridNode* prev;
} GridNode;

typedef struct {
    GridNode* head; // Pointer ke node pertama
    int cellSize;
    Texture2D blockTextures[7];
} Grid;

typedef struct {
    int row;
    int column;
} WallKickOffset;

extern int startX;
extern int startY;

void Position_Init(Position *pos, int row, int column);
void Block_Init(Block *block);
void Block_Draw(Block *block, int offsetX, int offsetY);
void Grid_Init(Grid *grid);
void Grid_Draw(Grid *grid, int offsetX, int offsetY);
void LoadGridTextures(Grid *grid);
WallKickOffset* getWallKickOffsets(char blockType, int rotationFrom, int rotationTo);
int IsValidPosition(Block *block, Grid *grid);
GridNode* Grid_GetNode(Grid *grid, int row, int col);
void Grid_SetNode(Grid *grid, int row, int col, int blockId);

#endif