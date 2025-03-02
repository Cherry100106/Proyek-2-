#include <stdio.h>
#include "raylib.h"
#include "Lib/movement.h"

#define BLOCK_SIZE 30
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 600

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris Animation");
    SetTargetFPS(60);  

    Block b = {5, 0, {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}}; 
    float lastDropTime = GetTime();
    float dropInterval = 0.5;  

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_RIGHT)) moveRight(&b);
        if (IsKeyPressed(KEY_LEFT)) moveLeft(&b);
        if (IsKeyPressed(KEY_DOWN)) moveDown(&b);

        if (GetTime() - lastDropTime >= dropInterval) {
            moveDown(&b);
            lastDropTime = GetTime();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b.shape[i][j]) {
                    DrawRectangle((b.x + j) * BLOCK_SIZE, (b.y + i) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLUE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();  
    return 0;
}
