// tsinan.c
#include "tsinan.h"
#include <stdio.h>

// Load high score from file
void loadHighScore(int *highScore) {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file) {
        fscanf(file, "%d", highScore);
        fclose(file);
    } else {
        *highScore = 0; // Default high score jika file tidak ditemukan
    }
}

// Save new high score to file
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
