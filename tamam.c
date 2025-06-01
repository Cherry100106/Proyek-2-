#include "tamam.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 550
#define SCREEN_HEIGHT 600

GameState currentScreen = MENU;
int selectedOption = 0;
float volume = 0.5f;
Music bgm;
Texture2D background;

MenuList menuList; 

void InitMenu(MenuList *list) {
    list->head = NULL;
    list->count = 0;
}

void AddMenuOption(MenuList *list, const char *option) {
    MenuNode *newNode = (MenuNode *)malloc(sizeof(MenuNode));
    newNode->option = option;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        MenuNode *temp = list->head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    list->count++;
}

const char* GetMenuOption(MenuList *list, int index) {
    if (index < 0 || index >= list->count) return NULL;
    MenuNode *temp = list->head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->option;
}

void FreeMenu(MenuList *list) {
    MenuNode *temp = list->head;
    while (temp != NULL) {
        MenuNode *toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    list->head = NULL;
    list->count = 0;
}

void InitMenuOptions() {
    InitMenu(&menuList);
    AddMenuOption(&menuList, "Play");
    AddMenuOption(&menuList, "Settings");
    AddMenuOption(&menuList, "Exit");
}


void InitAudioResources() {
    bgm = LoadMusicStream("Assets/BGM2.mp3");
    PlayMusicStream(bgm);
    SetMusicVolume(bgm, volume);
}

void UnloadAudioResources() {
    UnloadMusicStream(bgm);
}

void InitBackground() {
    background = LoadTexture("Assets/Background2.jpg");
}

void UnloadBackground() {
    UnloadTexture(background);
}

void DrawBackground() {
    float scaleX = (float)SCREEN_WIDTH / background.width;
    float scaleY = (float)SCREEN_HEIGHT / background.height;
    float scale = (scaleX > scaleY) ? scaleX : scaleY;

    Rectangle source = { 0, 0, background.width, background.height };
    Rectangle dest = { 0, 0, background.width * scale, background.height * scale };
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

    for (int i = 0; i < menuList.count; i++) {
        Color color = (i == selectedOption) ? GREEN : WHITE;
        const char *text = GetMenuOption(&menuList, i);
        if (text != NULL)
            DrawCenteredText(text, 200 + (i * 60), 40, color);
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
    int optCount = menuList.count;
    if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + optCount) % optCount;
    if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % optCount;
    if (IsKeyPressed(KEY_ENTER)) {
        const char *selected = GetMenuOption(&menuList, selectedOption);
        if (selected != NULL) {
            if (strcmp(selected, "Play") == 0) currentScreen = PLAY;
            else if (strcmp(selected, "Settings") == 0) currentScreen = SETTINGS;
            else if (strcmp(selected, "Exit") == 0) currentScreen = EXIT;
        }
    }
}

void HandleSettingsInput() {
    if (IsKeyDown(KEY_RIGHT)) volume += 0.06f;
    if (IsKeyDown(KEY_LEFT)) volume -= 0.06f;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;

    if (volume > 1.0f) volume = 1.0f;
    if (volume < 0.0f) volume = 0.0f;

    SetMusicVolume(bgm, volume);
}
