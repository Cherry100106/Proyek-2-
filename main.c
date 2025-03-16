#include "wafi.h"
#include "farell.h"
#include "nashwa.h"

int main() {
    const int screenWidth = 550;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Tetris Kelompok 1A");

    Texture2D background = LoadTexture("Assets/Background.png");
    Texture2D frameTexture = LoadTexture("Assets/frame.png");
    Texture2D papanScore = LoadTexture("Assets/Papanscore.png");
    InitAudioDevice();
    Music music = LoadMusicStream("Assets/Backsound_Korobeiniki_SonyaBelousova.wav"); 
    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);
    Sound clearSound = LoadSound("Assets/sound_blokhancur.wav");
    SetSoundVolume(clearSound, 1.0f);

    Grid grid;
    Grid_Init(&grid);

    Block currentBlock;
    Block_Init(&currentBlock);

    SetTargetFPS(60);

    int gravityCounter = 0;
    const int gravityDelay = 30;
    int score = 0;

    while (!WindowShouldClose()) {

        UpdateMusicStream(music);
        gravityCounter++;
        if (gravityCounter >= gravityDelay) {
            gravityCounter = 0;
            moveDown(&currentBlock, &grid);
        }

        // Operasi Pergerakan
        if (IsKeyPressed(KEY_LEFT)) moveLeft(&currentBlock, &grid); 
        if (IsKeyPressed(KEY_RIGHT)) moveRight(&currentBlock, &grid);
        if (IsKeyPressed(KEY_UP)) rotateBlock(&currentBlock, &grid); 
        if (IsKeyPressed(KEY_DOWN)) moveDown(&currentBlock, &grid);
        if (IsKeyPressed(KEY_SPACE)) skipBawah(&currentBlock, &grid);

        if (CheckCollision(&currentBlock, &grid, 0, 1)) {
            PlaceTetromino(&currentBlock, &grid);
            int rowCleared = ClearRows(&grid);
            score += rowCleared;
            if (rowCleared > 0) {
                PlaySound(clearSound);
            }
            Block_Init(&currentBlock); // Spawn blok baru
            if (CheckGameOver(&grid)) break;
        }

        // Merender tetris
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(background,360,0, WHITE);
            DrawTexture(frameTexture,0,0, WHITE);
            DrawTexture(papanScore, 365, 100, WHITE);
            Grid_Draw(&grid,30,30);
            Block_Draw(&currentBlock, 30, 30);
            DrawText(TextFormat("SCORE"), 395, 50, 40, WHITE);
            DrawText(TextFormat("%d",score), 445, 110, 30, WHITE);
        EndDrawing();
    }

    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
    UnloadTexture(frameTexture);
    UnloadTexture(background);
    UnloadTexture(papanScore);
    CloseWindow();
    return 0;
}