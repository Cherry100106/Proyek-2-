#ifndef TSINAN_H
#define TSINAN_H

#define HIGHSCORE_FILE "highscore.txt"

void loadHighScore(int *highScore);
void saveHighScore(int score);
int getHighScore();
void displayHighScore(int offsetX, int offsetY);

#endif
