#include <raylib.h>
#include "grid.h"
#include "block.h"
#include "posisi.h"

int main() {
    const int screenWidth = 300;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Rusak");
    SetTargetFPS(60);

    Grid grid;
    Grid_Init(&grid);

    LBlock lblock;
    LBlock_Init(&lblock);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);

        Grid_Draw(&grid);
        Block_Draw((Block*)&lblock, 100, 100);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
