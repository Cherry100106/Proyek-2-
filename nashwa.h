#ifndef NASHWA_H
#define NASHWA_H

#include "wafi.h"
#include "farell.h"
#include <stdbool.h>

bool CheckCollision(Block *block, Grid *grid, int dx, int dy);
void PlaceTetromino(Block *block, Grid *grid);
bool CheckGameOver(Grid *grid);
int ClearRows(Grid *grid, int *combo);
int ApplyComboScore(int rowsCleared, int *combo);
void ResetGame(Grid *grid, Block *currentBlock, Block *nextBlocks, int *score, int *combo, Block *holdBlock, bool *hasHeld);
bool HandleGameOver();

#endif