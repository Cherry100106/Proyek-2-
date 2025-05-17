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
//fungsi rotasi blok
void rotateBlock(Block *block, Grid *grid) {
    int nextRotation = (block->rotationState + 1) % 4;  // Rotasi berikutnya

    // Ambil pivot dari rotasi saat ini
    Position pivot = block->cells[block->rotationState][0];  

    Position tempCells[4];
    for (int i = 0; i < 4; i++) {
        int relRow = block->cells[nextRotation][i].row - block->cells[nextRotation][0].row;
        int relCol = block->cells[nextRotation][i].column - block->cells[nextRotation][0].column;
        
        // Terapkan rotasi dengan mempertahankan pivot
        tempCells[i].row = pivot.row + relRow;
        tempCells[i].column = pivot.column + relCol;
    }

    bool canRotate = false;
    int finalOffsetRow = 0, finalOffsetCol = 0;

    // Ambil Wall Kick Offset
    WallKickOffset wallKickOffsets[5];
    if (block->blockType != 'O') {
        WallKickOffset* tempOffsets = getWallKickOffsets(block->blockType, block->rotationState, nextRotation);
        for (int i = 0; i < 5; i++) {
            wallKickOffsets[i] = tempOffsets[i];
        }
    } else {
        for (int i = 0; i < 5; i++) {
            wallKickOffsets[i].row = 0;
            wallKickOffsets[i].column = 0;
        }
    }

    // Coba setiap wall kick offset
    for (int k = 0; k < 5; k++) {
        int testOffsetRow = wallKickOffsets[k].row;
        int testOffsetCol = wallKickOffsets[k].column;

        bool validPosition = true;
        for (int i = 0; i < 4; i++) {
            int row = tempCells[i].row + testOffsetRow;
            int col = tempCells[i].column + testOffsetCol;

            // Periksa apakah posisi valid
            if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS || grid->grid[row][col]) {
                validPosition = false;
                break;
            }
        }

        // Jika posisi valid, simpan offset dan keluar dari loop
        if (validPosition) {
            canRotate = true;
            finalOffsetRow = testOffsetRow;
            finalOffsetCol = testOffsetCol;
            break;
        }
    }

    // Jika bisa rotasi, update posisi blok
    if (canRotate) {
        block->rotationState = nextRotation;

        // Update posisi blok dengan mempertahankan pivot
        for (int i = 0; i < 4; i++) {
            block->cells[nextRotation][i].row = tempCells[i].row + finalOffsetRow;
            block->cells[nextRotation][i].column = tempCells[i].column + finalOffsetCol;
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

/* #include "farell.h"

// Fungsi gerak blok kiri
void moveLeft(Block *block, Grid *grid) {
    block->col--; // Coba geser ke kiri
    if (!IsValidPosition(block, grid)) {
        block->col++; // Kembalikan jika tidak valid
    }
}

// Fungsi gerak blok kanan
void moveRight(Block *block, Grid *grid) {
    block->col++; // Coba geser ke kanan
    if (!IsValidPosition(block, grid)) {
        block->col--; // Kembalikan jika tidak valid
    }
}

// Fungsi gerak blok bawah (agak dipercepat)
void moveDown(Block *block, Grid *grid) {
    block->row++; // Coba turun
    if (!IsValidPosition(block, grid)) {
        block->row--; // Kembalikan jika tidak valid
    }
}

// Fungsi rotasi blok
void rotateBlock(Block *block, Grid *grid) {
    int nextRotation = (block->rotationState + 1) % 4;
    int originalRotation = block->rotationState;
    int originalRow = block->row;
    int originalCol = block->col;

    // Coba rotasi
    block->rotationState = nextRotation;

    // Ambil Wall Kick Offset
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

    // Coba setiap wall kick offset
    for (int k = 0; k < 5; k++) {
        block->row = originalRow + wallKickOffsets[k].row;
        block->col = originalCol + wallKickOffsets[k].column;
        if (IsValidPosition(block, grid)) {
            return; // Rotasi berhasil
        }
    }

    // Jika tidak ada posisi valid, kembalikan ke keadaan awal
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

    // Render ghost piece dengan warna transparan
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
}*/