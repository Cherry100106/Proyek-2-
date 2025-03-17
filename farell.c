#include "farell.h"

void moveLeft(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int newCol = block->cells[block->rotationState][i].column - 1;
        int row = block->cells[block->rotationState][i].row;
        if (newCol < 0 || grid->grid[row][newCol]) return;
    }
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].column--;
    }
}

void moveRight(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int newCol = block->cells[block->rotationState][i].column + 1;
        int row = block->cells[block->rotationState][i].row;
        if (newCol >= NUM_COLS || grid->grid[row][newCol]) return;
    }
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].column++;
    }
}

void moveDown(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int newRow = block->cells[block->rotationState][i].row + 1;
        int col = block->cells[block->rotationState][i].column;
        if (newRow >= NUM_ROWS || grid->grid[newRow][col]) return;
    }
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].row++;
    }
}

void rotateBlock(Block *block, Grid *grid) {
    int nextRotation = (block->rotationState + 1) % 4;
    int pivotRow = block->cells[block->rotationState][0].row;
    int pivotCol = block->cells[block->rotationState][0].column;

    Position tempCells[4];
    for (int i = 0; i < 4; i++) {
        tempCells[i].row = block->cells[nextRotation][i].row;
        tempCells[i].column = block->cells[nextRotation][i].column;
    }

    int offsetRow = pivotRow - tempCells[0].row;
    int offsetCol = pivotCol - tempCells[0].column;

    bool canRotate = true;
    for (int i = 0; i < 4; i++) {
        int row = tempCells[i].row + offsetRow;
        int col = tempCells[i].column + offsetCol;
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS || grid->grid[row][col]) {
            canRotate = false;
            break;
        }
    }
    if (canRotate) {
        block->rotationState = nextRotation;
        for (int i = 0; i < 4; i++) {
            block->cells[block->rotationState][i].row = tempCells[i].row + offsetRow;
            block->cells[block->rotationState][i].column = tempCells[i].column + offsetCol;
        }
    }
}

void skipBawah(Block *block, Grid *grid){
    int i;
    int newRow;
    int col;
    while (true) {
        bool canMoveDown = true;
        for (i = 0; i < 4; i++){
            newRow = block->cells[block->rotationState][i].row +1;
            col = block->cells[block->rotationState][i].column;
            if (newRow >= NUM_ROWS || grid->grid[newRow][col]) {
                canMoveDown = false;
                break;
            }
        }
        if (canMoveDown) {
            for (int i = 0; i < 4; i++) {
                block->cells[block->rotationState][i].row++;
            }
        } else {
            break;
        }
    }
}

void DrawNextBlocks(Block nextBlocks[], int offsetX, int offsetY) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int row = nextBlocks[i].cells[nextBlocks[i].rotationState][j].row;
            int col = nextBlocks[i].cells[nextBlocks[i].rotationState][j].column;

            DrawRectangle(
                offsetX + col * nextBlocks[i].cellSize,
                offsetY + (i * 4 + row) * nextBlocks[i].cellSize,
                nextBlocks[i].cellSize, nextBlocks[i].cellSize,
                nextBlocks[i].colors[nextBlocks[i].id % 7]
            );

            DrawRectangleLines(
                offsetX + col * nextBlocks[i].cellSize,
                offsetY + (i * 4 + row) * nextBlocks[i].cellSize,
                nextBlocks[i].cellSize, nextBlocks[i].cellSize,
                BLACK
            );
        }
    }
}