#ifndef COLORS_H
#define COLORS_H
#include <raylib.h>
#define CYAN (Color){0, 255, 255, 255}

static const Color COLORS[8] = {
    RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK, WHITE
};
void Colors_Init(Color colors[8]);
#endif
