#include "raylib.h"
#include <stdio.h>

int main() {
    printf("Starting program...\n");

    InitWindow(800, 600, "Hello Raylib!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 300, 280, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();

    printf("Program exited successfully.\n");
    return 0;
}
