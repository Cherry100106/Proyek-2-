#include <stdio.h>
#include "raylib.h"
#include "Lib/movement.h"
#include "Lib/background.h"
#include "constans.h"


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);  

    LoadBackground();

    Block b = {5, 0, {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}}; 
    float lastDropTime = GetTime();
    float dropInterval = 0.5;  

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBackground();

        if (IsKeyPressed(KEY_RIGHT)) moveRight(&b);
        if (IsKeyPressed(KEY_LEFT)) moveLeft(&b);
        if (IsKeyPressed(KEY_DOWN)) moveDown(&b);

        if (GetTime() - lastDropTime >= dropInterval) {
            moveDown(&b);
            lastDropTime = GetTime();
        }


        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b.shape[i][j]) {
                    DrawRectangle((b.x + j) * BLOCK_SIZE, (b.y + i) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLUE);
                }
            }
        }

        EndDrawing();
    }

    UnloadBackground();
    CloseWindow();  
    return 0;
}
