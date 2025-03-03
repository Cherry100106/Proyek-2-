#include "block.h"
#include "posisi.h"
#include "colors.h"

void LBlock_Init(LBlock *block) {
    block->super.id = 1;
    block->super.cellSize = 30;
    block->super.rotationState = 0; 
    block->super.colors[1] = ORANGE;  

    // Rotasi ke-0
    Position_Init(&block->super.cells[0][0], 0, 2);
    Position_Init(&block->super.cells[0][1], 1, 0);
    Position_Init(&block->super.cells[0][2], 1, 1);
    Position_Init(&block->super.cells[0][3], 1, 2);

    // Rotasi ke-1
    Position_Init(&block->super.cells[1][0], 0, 1);
    Position_Init(&block->super.cells[1][1], 1, 1);
    Position_Init(&block->super.cells[1][2], 2, 1);
    Position_Init(&block->super.cells[1][3], 2, 2);

    // Rotasi ke-2
    Position_Init(&block->super.cells[2][0], 1, 0);
    Position_Init(&block->super.cells[2][1], 1, 1);
    Position_Init(&block->super.cells[2][2], 1, 2);
    Position_Init(&block->super.cells[2][3], 2, 0);

    // Rotasi ke-3
    Position_Init(&block->super.cells[3][0], 0, 0);
    Position_Init(&block->super.cells[3][1], 0, 1);
    Position_Init(&block->super.cells[3][2], 1, 1);
    Position_Init(&block->super.cells[3][3], 2, 1);
}
