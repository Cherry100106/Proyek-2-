#ifndef FARELL_H
#define FARELL_H
#include "wafi.h"

void moveLeft(Block *block, Grid *grid);
void moveRight(Block *block, Grid *grid);
void moveDown(Block *block, Grid *grid);
void rotateBlock(Block *block, Grid *grid);
void skipBawah(Block *block, Grid *grid);
void DrawNextBlocks(Block nextBlocks[], int offsetX, int offsetY);
void DrawGhostPiece(Block *block, Grid *grid, int offsetX, int offsetY);
bool DrawCountdown();
void DrawHoldBlock(Block *holdBlock, int offsetX, int offsetY);
void HoldBlock(Block *currentBlock, Block *holdBlock, Block *nextBlocks, bool *hasHeld, Grid *grid);

#endif