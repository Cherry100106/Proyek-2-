#include "movement.h"

void moveLeft(Block *b) {
    if (b->x > 0) {  
        b->x--;
    }
}

void moveRight(Block *b) {
    if (b->x < GRID_WIDTH - 4) {  
        b->x++;
    }
}

void moveDown(Block *b) {
    if (b->y < GRID_HEIGHT - 4) {  
        b->y++; 
    }
}

void rotateBlock(Block *b) {
    int temp[4][4];

    //Rotasi langsung 90° searah jarum jam
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = b->shape[i][j];  
        }
    }

    // Copy hasil rotasi ke blok asli
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            b->shape[i][j] = temp[i][j];
        }
    }
}
