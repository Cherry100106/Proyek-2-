#ifndef POSISI_H
#define POSISI_H

typedef struct {
    int row;
    int column;
} Position;

void Position_Init(Position *pos, int row, int column);

#endif
