#include "wafi.h"
#include "farell.h"
#include "nashwa.h"

int main() {
    const int screenWidth = 300;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Tetris with Raylib");

    Grid grid;
    Grid_Init(&grid);

    Block currentBlock;
    Block_Init(&currentBlock);

    SetTargetFPS(60);

    int gravityCounter = 0;
    const int gravityDelay = 30; // Blok akan turun setiap 30 frame (0.5 detik jika FPS = 60)

    while (!WindowShouldClose()) {
        gravityCounter++;
        if (gravityCounter >= gravityDelay) {
            gravityCounter = 0;
            moveDown(&currentBlock, &grid); // Gerakkan blok ke bawah secara otomatis
        }

        // Handle input
        if (IsKeyPressed(KEY_LEFT)) moveLeft(&currentBlock, &grid); // Geser kiri
        if (IsKeyPressed(KEY_RIGHT)) moveRight(&currentBlock, &grid); // Geser kanan
        if (IsKeyPressed(KEY_UP)) rotateBlock(&currentBlock, &grid); // Rotasi blok

        // Update game state
        if (CheckCollision(&currentBlock, &grid, 0, 1)) {
            PlaceTetromino(&currentBlock, &grid);
            int score = ClearRows(&grid);
            Block_Init(&currentBlock); // Spawn blok baru
            if (CheckGameOver(&grid)) break;
        }

        // Render
        BeginDrawing();
            ClearBackground(RAYWHITE);
            Grid_Draw(&grid);
            Block_Draw(&currentBlock, 50, 50); // Contoh offset
        EndDrawing();
    }

    CloseWindow();
    return 0;
}