#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>
#include "posisi.h"
#include "colors.h"

typedef struct {
    int id;
    Position cells[4][4]; // 4 rotasi, masing-masing dengan 4 posisi
    int cellSize;
    int rotationState;
    Color colors[8];
} Block;

void Block_Init(Block *block);
void Block_Draw(Block *block, int offsetX, int offsetY);

typedef struct {
    Block super;
} LBlock;

void LBlock_Init(LBlock *block);
void LBlock_Draw(LBlock *block);

#endif
