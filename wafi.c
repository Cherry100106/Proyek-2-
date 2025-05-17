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

        // x x x x (Pusat rotasinya ada pada indeks 1)
        // . . . . 
        // . . . .
        // . . . .

            // Rotasi 90° 
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 2, startX);
            Position_Init(&block->cells[1][3], startY + 3, startX);

        // x . . .
        // x . . .
        // x . . . 
        // x . . .

            // Rotasi 180° 
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY, startX + 2);
            Position_Init(&block->cells[2][3], startY, startX + 3);

        // x x x x
        // . . . . 
        // . . . .
        // . . . . 

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 2, startX);
            Position_Init(&block->cells[3][3], startY + 3, startX);
            break;
        
        // x . . . 
        // x . . . 
        // x . . . 
        // x . . .

        case 1: // L
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY + 1, startX);
            Position_Init(&block->cells[0][2], startY + 2, startX);
            Position_Init(&block->cells[0][3], startY + 2, startX + 1);

        // . x . . 
        // . x . . (Pusat rotasinya ada pada indeks ke-2 )
        // . x x . 
        // . . . .

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX + 1);
            Position_Init(&block->cells[1][1], startY, startX);
            Position_Init(&block->cells[1][2], startY, startX + 2);
            Position_Init(&block->cells[1][3], startY + 1, startX + 2);
        
        // . . . . 
        // x x x . 
        // . . x . 
        // . . . .

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1); 
            Position_Init(&block->cells[2][2], startY + 1, startX);
            Position_Init(&block->cells[2][3], startY + 2, startX);
        
        // . . . . 
        // x x . .
        // . x . . 
        // . x . .

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 1, startX + 2);
            break;

        // . . . . 
        // . x . . 
        // . x x x 
        // . . . .

        case 2: // J
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX + 1);
            Position_Init(&block->cells[0][1], startY + 1, startX + 1);
            Position_Init(&block->cells[0][2], startY + 2, startX + 1);
            Position_Init(&block->cells[0][3], startY + 2, startX);

        // . . x . 
        // . . x . (Pusat rotasinya ada pada indeks ke-2)
        // . x x . 
        // . . . .

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY, startX + 1);
            Position_Init(&block->cells[1][2], startY, startX + 2);
            Position_Init(&block->cells[1][3], startY + 1, startX);

        // . . . . 
        // . x x x (Pusat rotasinya ada pada indeks ke-2)
        // . x . . 
        // . . . .

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX + 1);
            Position_Init(&block->cells[2][1], startY, startX);
            Position_Init(&block->cells[2][2], startY + 1, startX + 1);
            Position_Init(&block->cells[2][3], startY + 2, startX + 1);

        // . . . . 
        // . x x . 
        // . x . . 
        // . x . .

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX + 2);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 1, startX + 2);
            break;
            
        // . . . . 
        // . . x . 
        // x x x . 
        // . . . .

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
        // . . . . 
        // . x x . (No rotation center)
        // . x x . 
        // . . . .

        case 4: // S
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX + 1);
            Position_Init(&block->cells[0][1], startY, startX + 2);
            Position_Init(&block->cells[0][2], startY + 1, startX);
            Position_Init(&block->cells[0][3], startY + 1, startX + 1);

        // . . . . 
        // . . x x 
        // . x x . 
        // . . . .

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX + 1);

        // . . . . 
        // . . x  
        // . x x . 
        // . x . .

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

        // . . . . 
        // . . x . 
        // . x x x 
        // . . . .

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX);

        // . . . . 
        // . x . . 
        // . x x . 
        // . x . .

            // Rotasi 180°
            Position_Init(&block->cells[2][0], startY, startX);
            Position_Init(&block->cells[2][1], startY, startX + 1);
            Position_Init(&block->cells[2][2], startY, startX + 2);
            Position_Init(&block->cells[2][3], startY + 1, startX + 1);

        // . . . . 
        // x x x . 
        // . x . . 
        // . . . .

            // Rotasi 270°
            Position_Init(&block->cells[3][0], startY, startX + 1);
            Position_Init(&block->cells[3][1], startY + 1, startX);
            Position_Init(&block->cells[3][2], startY + 1, startX + 1);
            Position_Init(&block->cells[3][3], startY + 2, startX + 1);
            break;
        
        // . . . . 
        // . x . . 
        // x x . . 
        // . x . .

    case 6: // Z
            // Rotasi 0°
            Position_Init(&block->cells[0][0], startY, startX);
            Position_Init(&block->cells[0][1], startY, startX + 1);
            Position_Init(&block->cells[0][2], startY + 1, startX + 1);
            Position_Init(&block->cells[0][3], startY + 1, startX + 2);

        // . . . . 
        // . x x . (Pusat rotasinya ada pada indeks ke-1) 
        // . . x x 
        // . . . .

            // Rotasi 90°
            Position_Init(&block->cells[1][0], startY, startX + 1);
            Position_Init(&block->cells[1][1], startY + 1, startX);
            Position_Init(&block->cells[1][2], startY + 1, startX + 1);
            Position_Init(&block->cells[1][3], startY + 2, startX);
        
        // . . . . 
        // . . x . 
        // . x x . 
        // . x . .

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
WallKickOffset* getWallKickOffsets(char blockType, int rotationFrom, int rotationTo) {
    static WallKickOffset offsets[5];

    if (blockType == 'I') {  // Wall Kick untuk I-piece
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},  // 0 -> 1
            {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},  // 1 -> 2
            {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},  // 2 -> 3
            {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}   // 3 -> 0
        };

        int index = (rotationFrom * 2 + (rotationTo > rotationFrom ? 0 : 1)) % 4;
        for (int i = 0; i < 5; i++) {
            offsets[i].row = wallKickTable[index][i][1];
            offsets[i].column = wallKickTable[index][i][0];
        }
    } else {  // Wall Kick untuk J, L, S, T, Z
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},  // 0 -> 1
            {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},  // 1 -> 2
            {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},  // 2 -> 3
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}  // 3 -> 0
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
                int blockId = grid->grid[i][j] - 1;
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

/*#include "wafi.h"
#include <stdlib.h>
#include <time.h>

void Position_Init(Position *pos, int row, int column) {
    pos->row = row;
    pos->column = column;
}

int startX = NUM_COLS / 2 - 2;
int startY = 0;

void Block_Init(Block *block) {
    srand(time(NULL)); // Inisialisasi seed untuk rand
    block->id = rand() % 7;
    block->cellSize = 30;
    block->rotationState = 0;
    block->row = startY; // Posisi absolut baris
    block->col = startX; // Posisi absolut kolom
    block->blockType = "ILJOSTZ"[block->id]; // Inisialisasi blockType

    // Muat tekstur berdasarkan ID
    switch (block->id) {
        case 0: block->texture = LoadTexture("Assets/Block_I.png"); break; // I
        case 1: block->texture = LoadTexture("Assets/Block_L.png"); break; // L
        case 2: block->texture = LoadTexture("Assets/Block_J.png"); break; // J
        case 3: block->texture = LoadTexture("Assets/Block_O.png"); break; // O
        case 4: block->texture = LoadTexture("Assets/Block_S.png"); break; // S
        case 5: block->texture = LoadTexture("Assets/Block_T.png"); break; // T
        case 6: block->texture = LoadTexture("Assets/Block_Z.png"); break; // Z
    }

    // Definisi koordinat relatif untuk setiap tetromino dan rotasinya
    int tetrominoConfigs[7][4][4][2] = {
        // I
        {{{0,0}, {0,1}, {0,2}, {0,3}},    // 0°
         {{0,0}, {1,0}, {2,0}, {3,0}},    // 90°
         {{0,0}, {0,1}, {0,2}, {0,3}},    // 180°
         {{0,0}, {1,0}, {2,0}, {3,0}}},   // 270°

        // L
        {{{0,0}, {1,0}, {2,0}, {2,1}},    // 0°
         {{0,1}, {0,0}, {0,2}, {1,2}},    // 90°
         {{0,0}, {0,1}, {1,0}, {2,0}},    // 180°
         {{0,0}, {1,0}, {1,1}, {1,2}}},   // 270°

        // J
        {{{0,1}, {1,1}, {2,1}, {2,0}},    // 0°
         {{0,0}, {0,1}, {0,2}, {1,0}},    // 90°
         {{0,1}, {0,0}, {1,1}, {2,1}},    // 180°
         {{0,2}, {1,0}, {1,1}, {1,2}}},   // 270°

        // O
        {{{0,0}, {0,1}, {1,0}, {1,1}},    // 0°
         {{0,0}, {0,1}, {1,0}, {1,1}},    // 90°
         {{0,0}, {0,1}, {1,0}, {1,1}},    // 180°
         {{0,0}, {0,1}, {1,0}, {1,1}}},   // 270°

        // S
        {{{0,1}, {0,2}, {1,0}, {1,1}},    // 0°
         {{0,0}, {1,0}, {1,1}, {2,1}},    // 90°
         {{0,1}, {0,2}, {1,0}, {1,1}},    // 180°
         {{0,0}, {1,0}, {1,1}, {2,1}}},   // 270°

        // T
        {{{0,1}, {1,0}, {1,1}, {1,2}},    // 0°
         {{0,0}, {1,0}, {1,1}, {2,0}},    // 90°
         {{0,0}, {0,1}, {0,2}, {1,1}},    // 180°
         {{0,1}, {1,0}, {1,1}, {2,1}}},   // 270°

        // Z
        {{{0,0}, {0,1}, {1,1}, {1,2}},    // 0°
         {{0,1}, {1,0}, {1,1}, {2,0}},    // 90°
         {{0,0}, {0,1}, {1,1}, {1,2}},    // 180°
         {{0,1}, {1,0}, {1,1}, {2,0}}}    // 270°
    };

    // Inisialisasi posisi relatif
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

    if (blockType == 'I') {  // Wall Kick untuk I-piece
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},  // 0 -> 1
            {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},  // 1 -> 2
            {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},  // 2 -> 3
            {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}   // 3 -> 0
        };
        int index = (rotationFrom * 2 + (rotationTo > rotationFrom ? 0 : 1)) % 4;
        for (int i = 0; i < 5; i++) {
            offsets[i].row = wallKickTable[index][i][1];
            offsets[i].column = wallKickTable[index][i][0];
        }
    } else {  // Wall Kick untuk J, L, S, T, Z
        int wallKickTable[4][5][2] = {
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},  // 0 -> 1
            {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},      // 1 -> 2
            {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},     // 2 -> 3
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}    // 3 -> 0
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
    for (int i = 0; i < NUM_ROWS; i++) {
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
*/