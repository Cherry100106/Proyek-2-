#include "background.h"
#include "constans.h"

static Texture2D background;

void LoadBackground() {
    background = LoadTexture("Lib/Asset/background.png");
}

void DrawBackground() {
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},          
        (Vector2){0, 0}, 0.0f, WHITE);
}

void UnloadBackground() {
    UnloadTexture(background);
}
