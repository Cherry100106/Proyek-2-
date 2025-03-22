#include "tsinan.h"
#include <stdio.h>

// Menampilkan Highscore
void loadHighScore(int *highScore) {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file) {
        fscanf(file, "%d", highScore);
        fclose(file);
    } else {
        *highScore = 0; // Default high score jika file tidak ditemukan
    }
}

// Save highscore baru
void saveHighScore(int score) {
    int highScore;
    loadHighScore(&highScore);
    
    if (score > highScore) {
        FILE *file = fopen(HIGHSCORE_FILE, "w");
        if (file) {
            fprintf(file, "%d", score);
            fclose(file);
        }
    }
}

// Mendapatkan highscore terbaru untuk ditampilkan
int getHighScore() {
    int highScore;
    loadHighScore(&highScore);
    return highScore;
}

// Display highscore
void displayHighScore(int offsetX, int offsetY) {
    int highScore = getHighScore();
    DrawText(TextFormat("High Score: %d", highScore), offsetX, offsetY, 20, WHITE);
}
