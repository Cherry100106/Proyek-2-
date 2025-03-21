#include "wafi.h"
#include "farell.h"
#include "nashwa.h"
#include <stdlib.h>
#include <time.h>

int main() {
    const int screenWidth = 550;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Tetris Kelompok 1A");
    srand(time(NULL));
    
    // Load Assets
    Texture2D background = LoadTexture("Assets/Background.png");
    Texture2D frameTexture = LoadTexture("Assets/Background2.png");
    Texture2D papanScore = LoadTexture("Assets/Papanscore.png");
    
    // Audio Setup
    InitAudioDevice();
    Music music = LoadMusicStream("Assets/Backsound_Korobeiniki_SonyaBelousova.wav"); 
    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);
    Sound clearSound = LoadSound("Assets/sound_blokhancur.wav");
    SetSoundVolume(clearSound, 1.0f);

    // Inisialisasi game
    Grid grid;
    Grid_Init(&grid);

    Block currentBlock;
    Block nextBlocks[3];
    Block_Init(&currentBlock);
    for (int i = 0; i < 3; i++) {
        Block_Init(&nextBlocks[i]);
    }
    
    SetTargetFPS(60);

    int gravityCounter = 0;
    const int gravityDelay = 30;
    int score = 0;
    int combo = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        gravityCounter++;
        if (gravityCounter >= gravityDelay) {
            gravityCounter = 0;
            moveDown(&currentBlock, &grid);
        }

        if (IsKeyPressed(KEY_LEFT)) moveLeft(&currentBlock, &grid); 
        if (IsKeyPressed(KEY_RIGHT)) moveRight(&currentBlock, &grid);
        if (IsKeyPressed(KEY_UP)) rotateBlock(&currentBlock, &grid); 
        if (IsKeyPressed(KEY_DOWN)) moveDown(&currentBlock, &grid);
        if (IsKeyPressed(KEY_SPACE)) skipBawah(&currentBlock, &grid);

        if (CheckCollision(&currentBlock, &grid, 0, 1)) {
            PlaceTetromino(&currentBlock, &grid);
            int rowCleared = ClearRows(&grid, &combo);
            score += rowCleared;
            if (rowCleared > 0) {
                PlaySound(clearSound);
            }
            currentBlock = nextBlocks[0];
            for (int i = 0; i < 2; i++) {
                nextBlocks[i] = nextBlocks[i + 1];
            }
            Block_Init(&nextBlocks[2]);
            
            if (CheckGameOver(&grid)) {
                bool retry = HandleGameOver();
                if (retry) {
                    ResetGame(&grid, &currentBlock, nextBlocks, &score, &combo);
                    continue;
                } else {
                    break;
                }
            }            
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 360, 0, WHITE);
        DrawTexture(frameTexture, 0, 0, WHITE);
        DrawTexture(papanScore, 365, 100, WHITE);
        Grid_Draw(&grid, 30, 30);
        Block_Draw(&currentBlock, 30, 30);
        DrawNextBlocks(nextBlocks, 320, 290);
        DrawText("SCORE", 390, 50, 40, WHITE);
        DrawText(TextFormat("%d", score), 440, 110, 30, WHITE);
        DrawText("Next Block", 375, 200, 30, WHITE);
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