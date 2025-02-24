#include "raylib.h"
#include <stdio.h>

int main() {
    Color darkgrey = {26, 31, 40, 255};
    InitWindow(600, 800, "Tetris MAAMAT");
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(darkgrey);
        EndDrawing(); 
    }
    CloseWindow();
return 0;
}
