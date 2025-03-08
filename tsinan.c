#include "tsinan.h"
#include <stdio.h>

void rotateBlock(Block *b) {
    int temp[4][4] = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int newX = b->pivotX + (j - b->pivotY);
            int newY = b->pivotY - (i - b->pivotX);
            if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4) {
                temp[newY][newX] = b->shape[i][j];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            b->shape[i][j] = temp[i][j];
        }
    }
}

void moveBlockLeft(Block *b) {
    if (b->posX > 0) {
        b->posX--;  // Cegah keluar kiri
    }
}

void moveBlockRight(Block *b) {
    if (b->posX < SCREEN_WIDTH / CELL_SIZE - 4) {
        b->posX++;  // Cegah keluar kanan
    }
}

