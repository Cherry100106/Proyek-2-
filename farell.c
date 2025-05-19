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
    bool collision; // Pindahkan deklarasi di luar loop
    Vector2 newBlocks[4]; // Deklarasi array lokal
    bool isVertical;
    block->rotationState = nextRotation;

    for (int i = 0; i < 4; i++) {
        float x = block->blocks[i].x - block->center.x;
        float y = block->blocks[i].y - block->center.y;
        newBlocks[i].x = -y + block->center.x; // Rotasi 90 derajat berlawanan arah
        newBlocks[i].y = x + block->center.y;
    }

    collision = false;
    for (int i = 0; i < 4; i++) {
        int gridX = (int)(block->position.x + newBlocks[i].x);
        int gridY = (int)(block->position.y + newBlocks[i].y);
        if (gridX < 0 || gridX >= 10 || gridY >= 20 || (gridY >= 0 && grid->cells[gridY][gridX] != 0)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        for (int i = 0; i < 4; i++) {
            block->blocks[i] = newBlocks[i];
        }
        // Penyesuaian posisi khusus untuk I
        if (block->id == 0) {
            if (isVertical) { // Vertikal ke Horizontal
                block->position.x -= 1.5f; // Geser ke kiri
                block->position.y += 1.5f; // Geser ke bawah
                block->center = (Vector2){1.5f, 0}; // Ubah pusat rotasi untuk posisi horizontal
            } else { // Horizontal ke Vertikal
                block->position.x += 1.5f; // Geser ke kanan
                block->position.y -= 1.5f; // Geser ke atas
                block->center = (Vector2){0, 1.5f}; // Kembali ke pusat rotasi vertikal
            }
        }
    }

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

void DrawHoldBlock(Block *holdBlock, int offsetX, int offsetY) {
    if (holdBlock->id >= 0) { 
        for (int i = 0; i < 4; i++) {
            int row = holdBlock->cells[0][i].row; // Megunakan rotasi 0 untuk tampilan hold
            int col = holdBlock->cells[0][i].column;
            DrawTexture(holdBlock->texture, 
                        offsetX + col * holdBlock->cellSize, 
                        offsetY + row * holdBlock->cellSize, 
                        WHITE);
            DrawRectangleLines(offsetX + col * holdBlock->cellSize, 
                               offsetY + row * holdBlock->cellSize, 
                               holdBlock->cellSize, holdBlock->cellSize, 
                               BLACK);
        }
    }
}

void HoldBlock(Block *currentBlock, Block *holdBlock, Block *nextBlocks, bool *hasHeld, Grid *grid) {
    Block tempHold;
    if (*hasHeld) return; // Mencegah hold berulang pada tetromino yang sama

    Block temp = *currentBlock;
    // Reset posisi dan rotasi currentBlock
    temp.row = startY;
    temp.col = startX;
    temp.rotationState = 0;

    if (holdBlock->id < 0) { // Jika belum ada tetromino di hold
        *holdBlock = temp;
        *currentBlock = nextBlocks[0];
        for (int i = 0; i < 2; i++) {
            nextBlocks[i] = nextBlocks[i + 1];
        }
        Block_Init(&nextBlocks[2]);
    } else { // Jika sudah ada tetromino di hold, tukar dengan blok saat ini
        tempHold = *holdBlock;
        *holdBlock = temp;
        *currentBlock = tempHold;
    }

    // Reset posisi dan rotasi currentBlock setelah ditukar
    currentBlock->row = startY;
    currentBlock->col = startX;
    currentBlock->rotationState = 0;

    // Mempastikan posisi valid setelah hold
    if (!IsValidPosition(currentBlock, grid)) {
        // Jika tidak valid, kembalikan ke hold dan batalkan
        *currentBlock = temp;
        *holdBlock = *currentBlock;
        return;
    }

    *hasHeld = true; // Tandai bahwa hold sudah digunakan
}