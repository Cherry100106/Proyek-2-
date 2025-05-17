#include "farell.h"

// Fungsi gerak blok kiri
void moveLeft(Block *block, Grid *grid) {
    block->col--;
    if (!IsValidPosition(block, grid)) {
        block->col++;
    }
}

// Fungsi gerak blok kanan
void moveRight(Block *block, Grid *grid) {
    block->col++;
    if (!IsValidPosition(block, grid)) {
        block->col--;
    }
}

// Fungsi gerak blok bawah
void moveDown(Block *block, Grid *grid) {
    block->row++;
    if (!IsValidPosition(block, grid)) {
        block->row--;
    }
}

// Fungsi rotasi blok
void rotateBlock(Block *block, Grid *grid) {
    int nextRotation = (block->rotationState + 1) % 4;
    int originalRotation = block->rotationState;
    int originalRow = block->row;
    int originalCol = block->col;

    block->rotationState = nextRotation;

    WallKickOffset wallKickOffsets[5];
    if (block->blockType != 'O') {
        WallKickOffset* tempOffsets = getWallKickOffsets(block->blockType, originalRotation, nextRotation);
        for (int i = 0; i < 5; i++) {
            wallKickOffsets[i] = tempOffsets[i];
        }
    } else {
        for (int i = 0; i < 5; i++) {
            wallKickOffsets[i].row = 0;
            wallKickOffsets[i].column = 0;
        }
    }

    for (int k = 0; k < 5; k++) {
        block->row = originalRow + wallKickOffsets[k].row;
        block->col = originalCol + wallKickOffsets[k].column;
        if (IsValidPosition(block, grid)) {
            return;
        }
    }

    block->rotationState = originalRotation;
    block->row = originalRow;
    block->col = originalCol;
}

// Fungsi untuk langsung ke bawah
void skipBawah(Block *block, Grid *grid) {
    while (true) {
        block->row++;
        if (!IsValidPosition(block, grid)) {
            block->row--;
            break;
        }
    }
}

// Fungsi menambahkan next blok
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
    Block ghostBlock = *block;
    while (true) {
        ghostBlock.row++;
        if (!IsValidPosition(&ghostBlock, grid)) {
            ghostBlock.row--;
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        int row = ghostBlock.cells[ghostBlock.rotationState][i].row + ghostBlock.row;
        int col = ghostBlock.cells[ghostBlock.rotationState][i].column + ghostBlock.col;
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