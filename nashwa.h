#ifndef NASHWA_H
#define NASHWA_H

#include "wafi.h" 

bool CheckCollision(Block *block, Grid *grid, int dx, int dy);
void PlaceTetromino(Block *block, Grid *grid);
bool CheckGameOver(Grid *grid);
int ClearRows(Grid *grid);

#endif