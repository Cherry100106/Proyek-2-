#include "wafi.h"
#include <stdlib.h>
#include <time.h>

void Position_Init(Position *pos, int row, int column) {
    pos->row = row;
    pos->column = column;
}

int startX = NUM_COLS / 2 - 2;
int startY = 0;

void Block_Init(Block *block) {
    block->id = rand() % 7;
    block->cellSize = 30;
    block->rotationState = 0;
    block->row = startY;
    block->col = startX;
    block->blockType = "ILJOSTZ"[block->id];

    switch (block->id) {
        case 0: block->texture = LoadTexture("Assets/Block_I.png"); break;
        case 1: block->texture = LoadTexture("Assets/Block_L.png"); break;
        case 2: block->texture = LoadTexture("Assets/Block_J.png"); break;
        case 3: block->texture = LoadTexture("Assets/Block_O.png"); break;
        case 4: block->texture = LoadTexture("Assets/Block_S.png"); break;
        case 5: block->texture = LoadTexture("Assets/Block_T.png"); break;
        case 6: block->texture = LoadTexture("Assets/Block_Z.png"); break;
    }

    int tetrominoConfigs[7][4][4][2] = {
        {{{0,0}, {0,1}, {0,2}, {0,3}}, {{0,0}, {1,0}, {2,0}, {3,0}}, {{0,0}, {0,1}, {0,2}, {0,3}}, {{0,0}, {1,0}, {2,0}, {3,0}}},
        {{{0,0}, {1,0}, {2,0}, {2,1}}, {{0,1}, {0,0}, {0,2}, {1,2}}, {{0,0}, {0,1}, {1,0}, {2,0}}, {{0,0}, {1,0}, {1,1}, {1,2}}},
        {{{0,1}, {1,1}, {2,1}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1,0}}, {{0,1}, {0,0}, {1,1}, {2,1}}, {{0,2}, {1,0}, {1,1}, {1,2}}},
        {{{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}},
        {{{0,1}, {0,2}, {1,0}, {1,1}}, {{0,0}, {1,0}, {1,1}, {2,1}}, {{0,1}, {0,2}, {1,0}, {1,1}}, {{0,0}, {1,0}, {1,1}, {2,1}}},
        {{{0,1}, {1,0}, {1,1}, {1,2}}, {{0,0}, {1,0}, {1,1}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1,1}}, {{0,1}, {1,0}, {1,1}, {2,1}}},
        {{{0,0}, {0,1}, {1,1}, {1,2}}, {{0,1}, {1,0}, {1,1}, {2,0}}, {{0,0}, {0,1}, {1,1}, {1,2}}, {{0,1}, {1,0}, {1,1}, {2,0}}}
    };

    for (int rot = 0; rot < 4; rot++) {
        for (int i = 0; i < 4; i++) {
            Position_Init(&block->cells[rot][i], 
                          tetrominoConfigs[block->id][rot][i][0],
                          tetrominoConfigs[block->id][rot][i][1]);
        }
    }
}

WallKickOffset* getWallKickOffsets(char blockType, int rotationFrom, int rotationTo) {
    static WallKickOffset offsets[5];
    if (blockType == 'I') {
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
            {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
            {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
            {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}
        };
        int index = (rotationFrom * 2 + (rotationTo > rotationFrom ? 0 : 1)) % 4;
        for (int i = 0; i < 5; i++) {
            offsets[i].row = wallKickTable[index][i][1];
            offsets[i].column = wallKickTable[index][i][0];
        }
    } else {
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
            {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
            {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}
        };
        int index = (rotationFrom * 2 + (rotationTo > rotationFrom ? 0 : 1)) % 4;
        for (int i = 0; i < 5; i++) {
            offsets[i].row = wallKickTable[index][i][1];
            offsets[i].column = wallKickTable[index][i][0];
        }
    }
    return offsets;
}

void Block_Draw(Block *block, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row + block->row;
        int col = block->cells[block->rotationState][i].column + block->col;
        DrawTexture(block->texture, offsetX + col * block->cellSize, offsetY + row * block->cellSize, WHITE);
        DrawRectangleLines(offsetX + col * block->cellSize, offsetY + row * block->cellSize, block->cellSize, block->cellSize, BLACK);
    }
}

void LoadGridTextures(Grid *grid) {
    grid->blockTextures[0] = LoadTexture("Assets/Block_I.png");
    grid->blockTextures[1] = LoadTexture("Assets/Block_L.png");
    grid->blockTextures[2] = LoadTexture("Assets/Block_J.png");
    grid->blockTextures[3] = LoadTexture("Assets/Block_O.png");
    grid->blockTextures[4] = LoadTexture("Assets/Block_S.png");
    grid->blockTextures[5] = LoadTexture("Assets/Block_T.png");
    grid->blockTextures[6] = LoadTexture("Assets/Block_Z.png");
}

void Grid_Init(Grid *grid) {
    for (int i = 0; i < NUM_ROWS; i++)
        for (int j = 0; j < NUM_COLS; j++)
            grid->grid[i][j] = 0;
    grid->cellSize = 30;
}

void Grid_Draw(Grid *grid, int offsetX, int offsetY) {
    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++) {
            if (grid->grid[i][j]) {
                int blockId = grid->grid[i][j] - 1;
                DrawTexture(grid->blockTextures[blockId], offsetX + j * grid->cellSize, offsetY + i * grid->cellSize, WHITE);
                DrawRectangleLines(offsetX + j * grid->cellSize, offsetY + i * grid->cellSize, grid->cellSize, grid->cellSize, BLACK);
            } else {
                DrawRectangleLines(offsetX + j * grid->cellSize, offsetY + i * grid->cellSize, grid->cellSize, grid->cellSize, BLACK);
            }
        }
    }    
}

int IsValidPosition(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row + block->row;
        int col = block->cells[block->rotationState][i].column + block->col;
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS || grid->grid[row][col]) {
            return 0;
        }
    }
    return 1;
}