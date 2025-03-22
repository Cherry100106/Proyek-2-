#include <stdio.h>
#include "tsinan.h"

static int currentScore = 0;  // Menyimpan score sementara

// Menambah score pemain
void addScore(int points) {
    currentScore += points;
}

// Mengambil high score dari file
int getHighScore() {
    int highScore = 0;
    FILE *file = fopen("highscore.txt", "r");

    if (file != NULL) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    return highScore;
}

// Menyimpan high score ke file
void saveHighScore(int score) {
    int highScore = getHighScore();

    if (score > highScore) {
        FILE *file = fopen("highscore.txt", "w");
        if (file != NULL) {
            fprintf(file, "%d", score);
            fclose(file);
        }
    }
}

// Mengambil score saat ini
int getCurrentScore() {
    return currentScore;
}

// Reset score ke 0
void resetScore() {
    currentScore = 0;
}
