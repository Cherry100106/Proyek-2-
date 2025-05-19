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

typedef struct MenuNode {
    const char *option;
    struct MenuNode *next;
} MenuNode;

typedef struct {
    MenuNode *head;
    int count;
} MenuList;

extern MenuList menuList;              
void InitMenuOptions();                
void InitMenu(MenuList *list);
void AddMenuOption(MenuList *list, const char *option);
const char* GetMenuOption(MenuList *list, int index);
void FreeMenu(MenuList *list);


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
