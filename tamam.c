#include "tamam.h"

GameState currentScreen = MENU;
int selectedOption = 0;
float volume = 0.5f;
Music bgm;
Texture2D background; 

const char *menuOptions[] = {
    "Play",
    "Settings",
    "Exit"
};
const int totalOptions = 3;

void InitAudioResources() {
    bgm = LoadMusicStream("Assets/Backsound_Korobeiniki_SonyaBelousova.wav");
    PlayMusicStream(bgm);
    SetMusicVolume(bgm, volume);
}

void UnloadAudioResources() {
    UnloadMusicStream(bgm);
}

void InitBackground() {
    background = LoadTexture("Assets/Lobby.jpg");

void UnloadBackground() {
    UnloadTexture(background);
}

void DrawBackground() {
    Rectangle source = { 0, 0, background.width, background.height };  
    Rectangle dest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };  
    Vector2 origin = { 0, 0 };

    DrawTexturePro(background, source, dest, origin, 0.0f, WHITE);
}

void DrawCenteredText(const char *text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (SCREEN_WIDTH - textWidth) / 2, y, fontSize, color);
}

void DrawMenu() {
    DrawBackground();
    DrawCenteredText("TETRIS", 100, 60, WHITE);

    for (int i = 0; i < totalOptions; i++) {
        Color color = (i == selectedOption) ? GREEN : WHITE;
        DrawCenteredText(menuOptions[i], 200 + (i * 60), 40, color);
    }
}

void DrawSettings() {
    DrawBackground();
    DrawCenteredText("Settings", 100, 60, WHITE);
    DrawCenteredText("Volume", 200, 40, WHITE);
    
    DrawRectangle((SCREEN_WIDTH - 200) / 2, 250, 200, 10, WHITE);
    DrawRectangle((SCREEN_WIDTH - 200) / 2, 250, (int)(volume * 200), 10, GREEN);

    DrawCenteredText("Press W to return", 450, 20, RED);
}

void HandleMenuInput() {
    if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
    if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % totalOptions;
    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) currentScreen = PLAY;
        else if (selectedOption == 1) currentScreen = SETTINGS;
        else if (selectedOption == 2) currentScreen = EXIT;
    }
}

void HandleSettingsInput() {
    if (IsKeyDown(KEY_RIGHT)) volume += 0.06f; // kalau kurang berasa volume, gantinya disini
    if (IsKeyDown(KEY_LEFT)) volume -= 0.06f;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;

    if (volume > 1.0f) volume = 1.0f; // ini buat maksimalnya, bisa edit disini
    if (volume < 0.0f) volume = 0.0f;

    SetMusicVolume(bgm, volume);
}
