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
               
    switch (block->id) {
        case 0: // I
            block->texture = LoadTexture("Assets/Block_I.png");
            break;
        case 1: // L
            block->texture = LoadTexture("Assets/Block_L.png");
            break;
        case 2: // J
            block->texture = LoadTexture("Assets/Block_J.png");
            break;
        case 3: // O
            block->texture = LoadTexture("Assets/Block_O.png");
            break;
        case 4: // S
            block->texture = LoadTexture("Assets/Block_S.png");
            break;
        case 5: // T
            block->texture = LoadTexture("Assets/Block_T.png");
            break;
        case 6: // Z
            block->texture = LoadTexture("Assets/Block_Z.png");
            break;
    }
   

    // Inisialisasi bentuk blok berdasarkan ID
    switch (block->id) {
        case 0: // I
            // Rotasi 0° 
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY, startX + 1);
            Position_Init(&block->cells[0][2], startY, startX + 2);
            Position_Init(&block->cells[0][3], startY, startX + 3);

            // Rotasi 90° 
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 2, startX);
            Position_Init(&block->cells[1][3], startY + 3, startX);

            // Rotasi 180° 
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY, startX + 2);
            Position_Init(&block->cells[2][3], startY, startX + 3);

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 2, startX);
            Position_Init(&block->cells[3][3], startY + 3, startX);
            break;

        case 1: // L
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY + 1, startX);
            Position_Init(&block->cells[0][2], startY + 2, startX);
            Position_Init(&block->cells[0][3], startY + 2, startX + 1);

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX + 1);
            Position_Init(&block->cells[1][1], startY, startX);
            Position_Init(&block->cells[1][2], startY, startX + 2);
            Position_Init(&block->cells[1][3], startY + 1, startX + 2);

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY + 1, startX);
            Position_Init(&block->cells[2][3], startY + 2, startX);

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 1, startX + 2);
            break;

        case 2: // J
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX + 1);
            Position_Init(&block->cells[0][1], startY + 1, startX + 1);
            Position_Init(&block->cells[0][2], startY + 2, startX + 1);
            Position_Init(&block->cells[0][3], startY + 2, startX);

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY, startX + 1);
            Position_Init(&block->cells[1][2], startY, startX + 2);
            Position_Init(&block->cells[1][3], startY + 1, startX);

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX + 1);
            Position_Init(&block->cells[2][1], startY, startX);
            Position_Init(&block->cells[2][2], startY + 1, startX + 1);
            Position_Init(&block->cells[2][3], startY + 2, startX + 1);

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX + 2);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 1, startX + 2);
            break;

        case 3: // O
            // Rotasi 0°, 90°, 180°, 270°
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY, startX + 1);
            Position_Init(&block->cells[0][2], startY + 1, startX);
            Position_Init(&block->cells[0][3], startY + 1, startX + 1);
        
            for (int i = 1; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    block->cells[i][j] = block->cells[0][j];
                }
            }
            break;

        case 4: // S
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX + 1);
            Position_Init(&block->cells[0][1], startY, startX + 2);
            Position_Init(&block->cells[0][2], startY + 1, startX);
            Position_Init(&block->cells[0][3], startY + 1, startX + 1);

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX + 1);

            // Rotasi 180° 
            Position_Init(&block->cells[2][0], startY, startX + 1);
            Position_Init(&block->cells[2][1], startY, startX + 2);
            Position_Init(&block->cells[2][2], startY + 1, startX);
            Position_Init(&block->cells[2][3], startY + 1, startX + 1);

            // Rotasi 270° 
            Position_Init(&block->cells[3][0], startY, startX);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 2, startX + 1);
            break;

    case 5: // T
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX + 1);
            Position_Init(&block->cells[0][1], startY + 1, startX);
            Position_Init(&block->cells[0][2], startY + 1, startX + 1);
            Position_Init(&block->cells[0][3], startY + 1, startX + 2);

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX);

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY, startX + 2);
            Position_Init(&block->cells[2][3], startY + 1, startX + 1);

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX + 1);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 2, startX + 1);
            break;

    case 6: // Z
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY, startX + 1);
            Position_Init(&block->cells[0][2], startY + 1, startX + 1);
            Position_Init(&block->cells[0][3], startY + 1, startX + 2);

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX + 1);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX);

            // Rotasi 180° (sama dengan 0°)
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY + 1, startX + 1);
            Position_Init(&block->cells[2][3], startY + 1, startX + 2);

            // Rotasi 270° (sama dengan 90°)
            Position_Init(&block->cells[3][0], startY, startX + 1);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 2, startX);
            break;
        }
}


void Block_Draw(Block *block, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row;
        int col = block->cells[block->rotationState][i].column;

        DrawTexture(
            block->texture,
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            WHITE
        );

        DrawRectangleLines(
            offsetX + col * block->cellSize,
            offsetY + row * block->cellSize,
            block->cellSize, block->cellSize,
            BLACK
        );
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
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            grid->grid[i][j] = 0;
        }
    }
    grid->cellSize = 30;
}

void Grid_Draw(Grid *grid,int offsetX,int offsetY) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (grid->grid[i][j]) {
                int blockId = grid->grid[i][j] - 1; // ID blok disimpan di grid
                DrawTexture(
                    grid->blockTextures[blockId],
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    WHITE
                );
                
                DrawRectangleLines(
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    grid->cellSize, grid->cellSize,
                    BLACK
                );
            } else {
                DrawRectangleLines(
                    offsetX + j * grid->cellSize,
                    offsetY + i * grid->cellSize,
                    grid->cellSize, grid->cellSize,
                    BLACK
                );
            }
        }
    }
}