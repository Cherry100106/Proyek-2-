#ifndef MOVEMENT_H
#define MOVEMENT_H

#define BLOCK_SIZE 30
#define GRID_WIDTH 15
#define GRID_HEIGHT 20

typedef struct {
    int x, y;
    int shape[4][4];
} Block;

void moveLeft(Block *b);
void moveRight(Block *b);
void moveDown(Block *b);
void rotateBlock(Block *b);

#endif
