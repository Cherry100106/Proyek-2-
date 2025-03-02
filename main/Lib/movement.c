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
