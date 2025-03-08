#ifndef TSINAN_H
#define TSINAN_H

#ifndef MOVEMENT_H
#define MOVEMENT_H

#define CELL_SIZE 30
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 600

typedef struct {
    int shape[4][4];
    int posX, posY;
    int pivotX, pivotY; // Titik poros rotasi
} Block;

void rotateBlock(Block *b);
void moveBlockLeft(Block *b);
void moveBlockRight(Block *b);

#endif

