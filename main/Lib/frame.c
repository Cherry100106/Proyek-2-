#include "frame.h"

static Texture2D frame;

void LoadFrame() {
    frame = LoadTexture("Lib/assets/frame.png");
}

void DrawFrame() {
    DrawTexture(frame, 0, 0, WHITE);
}

void UnloadFrame() {
    UnloadTexture(frame);
}
