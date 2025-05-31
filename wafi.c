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
    block->position = (Vector2){4,0}; //Mulai dari atas tengah grid

    for (int i = 0; i < 4; i++) {
        block->blocks[i] = (Vector2){0, 0};
    }
    switch (block->id) {
        case 0: block->texture = LoadTexture("Assets/Block_I.png"); break;
        case 1: block->texture = LoadTexture("Assets/Block_L.png"); break;
        case 2: block->texture = LoadTexture("Assets/Block_J.png"); break;
        case 3: block->texture = LoadTexture("Assets/Block_O.png"); break;
        case 4: block->texture = LoadTexture("Assets/Block_S.png"); break;
        case 5: block->texture = LoadTexture("Assets/Block_T.png"); break;
        case 6: block->texture = LoadTexture("Assets/Block_Z.png"); break;
    }
    
    switch (block->id) 
    {
    case 0: // I
        block->blocks[0] = (Vector2) {0,0};
        block->blocks[1] = (Vector2) {0,1};
        block->blocks[2] = (Vector2) {0,2};
        block->blocks[3] = (Vector2) {0,3};
        block->center = (Vector2) {0,1.5f}; // Pusat rotasinya
        break;
    
    case 1: // O
        block->blocks[0] = (Vector2) {0,0};
        block->blocks[1] = (Vector2) {1,0};
        block->blocks[2] = (Vector2) {0,1};
        block->blocks[3] = (Vector2) {1,1};
        block->center = (Vector2) {0.5f,0.5f}; // Pusat rotasinya
        break;

    case 2: //T
        block->blocks[0] = (Vector2) {1,0};
        block->blocks[1] = (Vector2) {0,1};
        block->blocks[2] = (Vector2) {1,1};
        block->blocks[3] = (Vector2) {2,1};
        block->center = (Vector2) {1,1}; // Pusat rotasinya
        break;

    case 3: //S
        block->blocks[0] = (Vector2) {1,0};
        block->blocks[1] = (Vector2) {2,0};
        block->blocks[2] = (Vector2) {0,1};
        block->blocks[3] = (Vector2) {1,1};
        block->center = (Vector2) {0.5f,0.5f}; // Pusat rotasinya
        break;
        
    case 4: // Z
        block->blocks[0] = (Vector2) {0,0};
        block->blocks[1] = (Vector2) {1,0};
        block->blocks[2] = (Vector2) {0,1};
        block->blocks[3] = (Vector2) {1,1};
        block->center = (Vector2) {1.5f,0.5f}; // Pusat rotasinya
        break;

    case 5: // J
        block->blocks[0] = (Vector2) {0,0};
        block->blocks[1] = (Vector2) {0,1};
        block->blocks[2] = (Vector2) {1,1};
        block->blocks[3] = (Vector2) {2,1};
        block->center = (Vector2) {1,1}; // Pusat rotasinya
        break;

    case 6: // L
        block->blocks[0] = (Vector2) {0,0};
        block->blocks[1] = (Vector2) {0,1};
        block->blocks[2] = (Vector2) {1,1};
        block->blocks[3] = (Vector2) {2,1};
        block->center = (Vector2) {1,1}; // Pusat rotasinya
        break;
    }
    
    int tetrominoConfigs[7][4][4][2] = {
        // Ini merupakan representasi bentuk I
        {{{1,0}, {1,1}, {1,2}, {1,3}}, {{0,2}, {1,2}, {2,2}, {3,2}}, {{2,0}, {2,1}, {2,2}, {2,3}}, {{0,1}, {1,1}, {2,1}, {3,1}}},

        // Ini merupakan representasi bentuk L
        {{{0,2}, {1,0}, {1,1}, {1,2}}, {{0,1}, {1,1}, {2,1}, {2,2}}, {{1,0}, {1,1}, {1,2}, {2,0}}, {{0,0}, {0,1}, {1,1}, {2,1}}},

        // Ini merupakan representasi bentuk J
        {{{0,0}, {1,0}, {1,1}, {1,2}}, {{0,1}, {0,2}, {1,1}, {2,1}}, {{1,0}, {1,1}, {1,2}, {2,2}}, {{0,1}, {1,1}, {2,0}, {2,1}}},

        // Ini merupakan representasi bentuk O
        {{{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}}},

        // Ini merupakan representasi bentuk S
        {{{0,1}, {0,2}, {1,0}, {1,1}}, {{0,1}, {1,1}, {1,2}, {2,2}}, {{1,1}, {1,2}, {2,0}, {2,1}}, {{0,0}, {1,0}, {1,1}, {2,1}}},

        // Ini merupakan representasi bentuk T
        {{{0,1}, {1,0}, {1,1}, {1,2}}, {{0,1}, {1,1}, {1,2}, {2,1}}, {{1,0}, {1,1}, {1,2}, {2,1}}, {{0,1}, {1,0}, {1,1}, {2,1}}},

        // Ini merupakan representasi bentuk Z
        {{{0,0}, {0,1}, {1,1}, {1,2}}, {{0,2}, {1,1}, {1,2}, {2,1}}, {{1,0}, {1,1}, {2,1}, {2,2}}, {{0,1}, {1,0}, {1,1}, {2,0}}}
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
    grid->head = NULL;
    grid->cellSize = 30;
}

GridNode* Grid_GetNode(Grid *grid, int row, int col) {
    GridNode* current = grid->head;
    while (current) {
        if (current->row == row && current->col == col) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void Grid_SetNode(Grid *grid, int row, int col, int blockId) {
    GridNode* node = Grid_GetNode(grid, row, col);
    if (blockId == 0) {
        // Hapus node jika blockId = 0
        if (node) {
            if (node->prev) {
                node->prev->next = node->next;
            } else {
                grid->head = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }
            free(node);
        }
        return;
    }
    // Jika node sudah ada, perbarui blockId
    if (node) {
        node->blockId = blockId;
        return;
    }
    // Buat node baru
    GridNode* newNode = (GridNode*)malloc(sizeof(GridNode));
    newNode->row = row;
    newNode->col = col;
    newNode->blockId = blockId;
    newNode->next = grid->head;
    newNode->prev = NULL;
    if (grid->head) {
        grid->head->prev = newNode;
    }
    grid->head = newNode;
}

void Grid_Draw(Grid *grid, int offsetX, int offsetY) {
    // Gambar semua sel sebagai kotak kosong terlebih dahulu
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            DrawRectangleLines(offsetX + j * grid->cellSize, offsetY + i * grid->cellSize, 
                               grid->cellSize, grid->cellSize, BLACK);
        }
    }
    // Gambar sel yang terisi dari linked list
    GridNode* current = grid->head;
    while (current) {
        if (current->blockId > 0) {
            int blockId = current->blockId - 1;
            DrawTexture(grid->blockTextures[blockId], 
                        offsetX + current->col * grid->cellSize, 
                        offsetY + current->row * grid->cellSize, WHITE);
            DrawRectangleLines(offsetX + current->col * grid->cellSize, 
                               offsetY + current->row * grid->cellSize, 
                               grid->cellSize, grid->cellSize, BLACK);
        }
        current = current->next;
    }
}


int IsValidPosition(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row + block->row;
        int col = block->cells[block->rotationState][i].column + block->col;
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
            return 0;
        }
        GridNode* node = Grid_GetNode(grid, row, col);
        if (node && node->blockId > 0) {
            return 0;
        }
    }
    return 1;
}

