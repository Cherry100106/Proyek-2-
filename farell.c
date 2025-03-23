#include "farell.h"
#include "nashwa.h"

// fungsi gerak blok kiri
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

// fungsi gerak blok kanan
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

//fungsi gerak blok bawah (agak dipercepat)
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

//fungsi rotasi blok
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

//fungsi untuk langsung kebawah
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

//fungsi menambahkan next blok
void DrawNextBlocks(Block nextBlocks[], int offsetX, int offsetY) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int row = nextBlocks[i].cells[nextBlocks[i].rotationState][j].row;
            int col = nextBlocks[i].cells[nextBlocks[i].rotationState][j].column;

            DrawTexture(
                nextBlocks[i].texture,
                offsetX + col * nextBlocks[i].cellSize,
                offsetY + (i * 4 + row) * nextBlocks[i].cellSize,
                WHITE
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

void DrawGhostPiece(Block *block, Grid *grid, int offsetX, int offsetY) {
    Block ghostBlock = *block; // Menyalin blok saat ini ke ghostBlock
    while (!CheckCollision(&ghostBlock, grid, 0, 1)) {
        for (int i = 0; i < 4; i++) {
            ghostBlock.cells[ghostBlock.rotationState][i].row++;
        }
    }

    // Render ghost piece dengan warna transparan
    for (int i = 0; i < 4; i++) {
        int row = ghostBlock.cells[ghostBlock.rotationState][i].row;
        int col = ghostBlock.cells[ghostBlock.rotationState][i].column;

        DrawTexture(
            ghostBlock.texture,
            offsetX + col * ghostBlock.cellSize,
            offsetY + row * ghostBlock.cellSize,
            (Color){255, 255, 255, 100}
        );

        DrawRectangleLines(
            offsetX + col * ghostBlock.cellSize,
            offsetY + row * ghostBlock.cellSize,
            ghostBlock.cellSize, ghostBlock.cellSize,
            (Color){0, 0, 0, 100}
        );
    }
}

bool DrawCountdown() {
    const char* countdownTexts[] = {"3", "2", "1", "Go!!"};
    const int durasicountdown = 60;
    static int countdownsaatini = 0;
    static int frames = 0;

    if (countdownsaatini >= 4) {
        countdownsaatini = 0;
        frames = 0;
        return true;
    }

    // Render countdown
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(countdownTexts[countdownsaatini], 
                 GetScreenWidth() / 2 - MeasureText(countdownTexts[countdownsaatini], 40) / 2, 
                 GetScreenHeight() / 2 - 20, 
                 40, BLACK);
    EndDrawing();
    frames++;
    if (frames >= durasicountdown) {
        frames = 0;
        countdownsaatini++;
    }

    return false;
}