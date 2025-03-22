#include "tsinan.h"
#include <stdio.h>

static int score = 0;
static int highScore = 0;
const char *highScoreFile = "highscore.txt";

void initScore() {
    score = 0;
    loadHighScore();
}

void addScore(int linesCleared) {
    int points[] = {0, 40, 100, 300, 1200};
    score += points[linesCleared];
}

void saveHighScore() {
    if (score > highScore) {
        highScore = score;
        FILE *file = fopen(highScoreFile, "w");
        if (file) {
            fprintf(file, "%d", highScore);
            fclose(file);
        }
    }
}

void loadHighScore() {
    FILE *file = fopen(highScoreFile, "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
}

int getScore() {
    return score;
}
