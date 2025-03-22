#ifndef TSINAN_H
#define TSINAN_H

void addScore(int points);         // Menambah score pemain
int getHighScore();                // Mengambil high score dari file
void saveHighScore(int score);     // Menyimpan high score ke file
void resetScore();                 // Reset score ke 0
int getCurrentScore();             // Ambil score saat ini

#endif
