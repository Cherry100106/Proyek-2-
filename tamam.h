#ifndef TAMAM_H
#define TAMAM_H

#include "raylib.h"


typedef enum {
    MENU,
    SETTINGS,
    PLAY,
    EXIT
} GameState;

extern GameState currentScreen;
extern int selectedOption;
extern float volume;
extern Music bgm;
extern Texture2D background;

void InitAudioResources();
void UnloadAudioResources();
void InitBackground();
void UnloadBackground();
void DrawBackground();
void DrawMenu();
void DrawSettings();
void HandleMenuInput();
void HandleSettingsInput();
void DrawCenteredText(const char *text, int y, int fontSize, Color color);

#endif