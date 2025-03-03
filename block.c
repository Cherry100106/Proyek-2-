#include "block.h"
#include "posisi.h"

void Block_Init(Block *block) {
    block->id = 0;
    block->cellSize = 30;
    block->rotationState = 0;

    // Warna default untuk blok
    block->colors[0] = RED;
    block->colors[1] = ORANGE;
    block->colors[2] = YELLOW;
    block->colors[3] = GREEN;
    block->colors[4] = BLUE;
    block->colors[5] = PURPLE;
    block->colors[6] = PINK;
    block->colors[7] = WHITE;
}

void Block_Draw(Block *block, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row;
        int col = block->cells[block->rotationState][i].column;

        DrawRectangle(
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            block->cellSize, block->cellSize,
            block->colors[block->id % 8]
        );

        DrawRectangleLines(
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            block->cellSize, block->cellSize,
            BLACK
        );
    }
}
