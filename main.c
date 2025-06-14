#include "wafi.h"
#include "farell.h"
#include "nashwa.h"
#include "tsinan.h"
#include "tamam.h"
#include <stdlib.h>
#include <time.h>

int main() {
    const int screenWidth = 550;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Tetris Kelompok 1A");
    InitAudioDevice();
    srand(time(NULL));

    InitMenuOptions();

    Texture2D background = LoadTexture("Assets/Background2.jpg");
    Texture2D frameTexture = LoadTexture("Assets/Frame10.png");
    Texture2D papanScore = LoadTexture("Assets/papanScore1.png");

    InitAudioResources();
    InitBackground();

    Music musicgameplay = LoadMusicStream("Assets/Backsound_Korobeiniki_SonyaBelousova.wav"); 
    Sound clearSound = LoadSound("Assets/sound_blokhancur.wav");
    SetSoundVolume(clearSound, 1.0f);

    Grid grid;
    Grid_Init(&grid);
    LoadGridTextures(&grid);

    Block currentBlock;
    Block nextBlocks[3];
    Block holdBlock = { .id = -1 };
    bool hasHeld = false; 
    Block_Init(&currentBlock);
    for (int i = 0; i < 3; i++) {
        Block_Init(&nextBlocks[i]);
    }

    SetTargetFPS(60);

    int gravityCounter = 0;
    const int gravityDelay = 30;
    int score = 0;
    int combo = 0;
    bool paused = false;
    float musicVolume = 1.0f;
    const float speedFade = 0.02f;
    int highScore = 0;
    loadHighScore(&highScore);
    bool countdownSelesai = false;

    while (!WindowShouldClose()) {
        if (!paused) {
            UpdateMusicStream(bgm);
            UpdateMusicStream(musicgameplay);
        }

        switch (currentScreen) {
            case MENU:
                if (IsMusicStreamPlaying(musicgameplay)) { 
                    musicVolume -= speedFade;
                    if (musicVolume <= 0.0f) {
                        StopMusicStream(musicgameplay);
                        musicVolume = 0.0f;
                    }
                    SetMusicVolume(musicgameplay, musicVolume);
                }
                if (!IsMusicStreamPlaying(bgm)) {
                    PlayMusicStream(bgm);
                    musicVolume = 0.0f;
                }
                if (musicVolume < 1.0f) {
                    musicVolume += speedFade;
                    SetMusicVolume(bgm, musicVolume);
                }
                HandleMenuInput();
                BeginDrawing();
                    DrawMenu();
                    displayHighScore(125,400);
                EndDrawing();
                break;

            case SETTINGS:
                if (IsMusicStreamPlaying(musicgameplay)) { 
                    musicVolume -= speedFade;
                    if (musicVolume <= 0.0f) {
                        StopMusicStream(musicgameplay);
                        musicVolume = 0.0f;
                    }
                    SetMusicVolume(musicgameplay, musicVolume);
                }
                if (!IsMusicStreamPlaying(bgm)) {
                    PlayMusicStream(bgm);
                    musicVolume = 0.0f;
                }
                if (musicVolume < 1.0f) {
                    musicVolume += speedFade;
                    SetMusicVolume(bgm, musicVolume);
                }
                HandleSettingsInput();
                BeginDrawing();
                    DrawSettings();
                EndDrawing();
                break;

            case PLAY:
                if (!countdownSelesai) {
                    countdownSelesai = DrawCountdown();
                    break;
                }
                if (IsMusicStreamPlaying(bgm)) {
                    musicVolume -= speedFade;
                    if (musicVolume <= 0.0f) {
                        StopMusicStream(bgm);
                        musicVolume = 0.0f;
                    }
                    SetMusicVolume(bgm, musicVolume);
                }
                if (!IsMusicStreamPlaying(musicgameplay)) {
                    PlayMusicStream(musicgameplay);
                    musicVolume = 0.0f;
                }
                if (musicVolume < 1.0f) {
                    musicVolume += speedFade;
                    SetMusicVolume(musicgameplay, musicVolume);
                }
                if (IsKeyPressed(KEY_P)) {
                    paused = !paused;
                    if (paused) {
                        PauseMusicStream(musicgameplay);
                    } else {
                        ResumeMusicStream(musicgameplay);
                    }
                }
                if (!paused) {
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
                    if (IsKeyPressed(KEY_C)) HoldBlock(&currentBlock, &holdBlock, nextBlocks, &hasHeld, &grid);

                    if (CheckCollision(&currentBlock, &grid, 0, 1)) {
                        PlaceTetromino(&currentBlock, &grid);
                        int rowCleared = ClearRows(&grid, &combo);
                        score += rowCleared;
                        if (rowCleared > 0) {
                            int baseScore = rowCleared * 100;
                            PlaySound(clearSound);
                        }
                        currentBlock = nextBlocks[0];
                        for (int i = 0; i < 2; i++) {
                            nextBlocks[i] = nextBlocks[i + 1];
                        }
                        Block_Init(&nextBlocks[2]);
                        hasHeld = false;
                        if (CheckGameOver(&grid)) {
                            saveHighScore(score);
                            if (HandleGameOver()) {
                                ResetGame(&grid, &currentBlock, nextBlocks, &score, &combo, &holdBlock, &hasHeld);
                                currentScreen = MENU;
                                countdownSelesai = false;
                            } else {
                                currentScreen = EXIT;
                            }
                        }
                    }
                }
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawTexture(background, 360, 0, WHITE);
                    DrawTexture(frameTexture, 0, 0, WHITE);
                    DrawTexture(papanScore, 365, 75, WHITE);
                    DrawGhostPiece(&currentBlock, &grid, 30, 30);
                    Grid_Draw(&grid, 30, 30);
                    Block_Draw(&currentBlock, 30, 30);
                    DrawNextBlocks(nextBlocks, 420, 320);
                    DrawHoldBlock(&holdBlock, 400, 200 );
                    DrawText(TextFormat("SCORE"), 390, 35, 30, WHITE);
                    DrawText(TextFormat("%d", score), 440, 85, 30, WHITE);
                    DrawText(TextFormat("Next Block"), 375, 280, 30, WHITE);
                    DrawText(TextFormat("Hold Block"), 375, 150, 30, WHITE);
                    if (paused) {
                        DrawText("PAUSED", screenWidth / 2 - 175, screenHeight / 2 - 20, 40, WHITE);
                    }
                EndDrawing();
                break;

            case EXIT:
                StopMusicStream(bgm);
                StopMusicStream(musicgameplay);
                CloseWindow();
                return 0;
        }
    }

    UnloadSound(clearSound);
    UnloadMusicStream(bgm);
    UnloadMusicStream(musicgameplay);
    UnloadAudioResources();
    UnloadTexture(frameTexture);
    UnloadTexture(background);
    UnloadTexture(papanScore);
    UnloadTexture(currentBlock.texture);
    UnloadTexture(holdBlock.texture);
    for (int i = 0; i < 3; i++) {
        UnloadTexture(nextBlocks[i].texture);
    }
    CloseAudioDevice();
    UnloadBackground();
    CloseWindow();
    return 0;
}
