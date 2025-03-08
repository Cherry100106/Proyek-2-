#include "raylib.h"
#include "tsinan.h"
#include <stdio.h>

#define CELL_SIZE 30
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 600

typedef struct {
    int shape[4][4];
    int posX, posY;
    int pivotX, pivotY; // Titik poros rotasi
} Block;

// Contoh blok T
Block createBlock() {
    Block b = {
        .shape = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0}
        },
        .posX = 3,
        .posY = 0,
        .pivotX = 1, // Poros rotasi di tengah blok
        .pivotY = 2
    };
    return b;
}

void rotateBlock(Block *b) {
    int temp[4][4];
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
    if (b->posX > 0) b->posX--;  // Cegah keluar kiri
}

void moveBlockRight(Block *b) {
    if (b->posX < SCREEN_WIDTH / CELL_SIZE - 4) b->posX++;  // Cegah keluar kanan
}

void DrawBlock(Block *b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b->shape[i][j] == 1) {
                DrawRectangle((b->posX + j) * CELL_SIZE, (b->posY + i) * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
            }
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris with Raylib");
    SetTargetFPS(60);

    Block currentBlock = createBlock();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_LEFT)) moveBlockLeft(&currentBlock);
        if (IsKeyPressed(KEY_RIGHT)) moveBlockRight(&currentBlock);
        if (IsKeyPressed(KEY_UP)) rotateBlock(&currentBlock);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBlock(&currentBlock);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

