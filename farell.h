#ifndef FARELL_H
#define FARELL_H

#include "wafi.h" // Menggunakan struktur Block dari Wafi

void moveLeft(Block *block, Grid *grid);
void moveRight(Block *block, Grid *grid);
void moveDown(Block *block, Grid *grid);
void rotateBlock(Block *block, Grid *grid);

#endif