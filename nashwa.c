#include "nashwa.h"
#include <stdlib.h>
#include <raylib.h>

bool CheckCollision(Block *block, Grid *grid, int dx, int dy) {
    Block tempBlock = *block;
    tempBlock.row += dy;
    tempBlock.col += dx;
    return !IsValidPosition(&tempBlock, grid);
}

void PlaceTetromino(Block *block, Grid *grid) {
    for (int i = 0; i < 4; i++) {
        int row = block->cells[block->rotationState][i].row + block->row;
        int col = block->cells[block->rotationState][i].column + block->col;
        if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
            Grid_SetNode(grid, row, col, block->id + 1);
        }
    }
}

bool CheckGameOver(Grid *grid) {
    GridNode* current = grid->head;
    while (current) {
        if (current->row == 0 && current->blockId > 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int ClearRows(Grid *grid, int *combo) {
    int rowsCleared = 0;
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        bool full = true;
        for (int col = 0; col < NUM_COLS; col++) {
            GridNode* node = Grid_GetNode(grid, row, col);
            if (!node || node->blockId == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            rowsCleared++;
            // Hapus semua node di baris ini
            GridNode* current = grid->head;
            GridNode* prev = NULL;
            while (current) {
                GridNode* next = current->next;
                if (current->row == row) {
                    if (prev) {
                        prev->next = next;
                    } else {
                        grid->head = next;
                    }
                    if (next) {
                        next->prev = prev;
                    }
                    free(current);
                } else {
                    prev = current;
                }
                current = next;
            }
            // Geser baris di atas ke bawah
            current = grid->head;
            while (current) {
                if (current->row < row) {
                    current->row++;
                }
                current = current->next;
            }
            row++; // Periksa baris yang sama lagi setelah penggeseran
        }
    }
    return ApplyComboScore(rowsCleared, combo);
}

int ApplyComboScore(int rowsCleared, int *combo) {
    if (rowsCleared == 5) {
        int bonus = (*combo) * 100;  
        (*combo)++; 
        return 500 + bonus;
    } else if (rowsCleared > 0) {
        *combo = 1;  
        return rowsCleared * 100;
    }
    return 0;
}

void ResetGame(Grid *grid, Block *currentBlock, Block *nextBlocks, int *score, int *combo, Block *holdBlock, bool *hasHeld ) {
    // Hapus semua node di linked list
    GridNode* current = grid->head;
    while (current) {
        GridNode* next = current->next;
        free(current);
        current = next;
    }
    grid->head = NULL;
    Grid_Init(grid);
    Block_Init(currentBlock);
    for (int i = 0; i < 3; i++) {
        Block_Init(&nextBlocks[i]);
    }
    *score = 0;
    *combo = 0;
    holdBlock->id = -1; // Reset holdBlock
    *hasHeld = false; // Reset hasHeld
}

bool HandleGameOver() {
    int screenWidth = 480;
    int screenHeight = 640;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
  
        int textGameOverX = (screenWidth - MeasureText("GAME OVER", 40)) / 2 + 30;
        int textGameOverY = 200;
        DrawText("GAME OVER", textGameOverX, textGameOverY, 40, RED);

        int buttonWidth = 220, buttonHeight = 50;
        int buttonX = (screenWidth - buttonWidth) / 2 + 30; 
        int textRetryX = buttonX + (buttonWidth - MeasureText("Retry", 25)) / 2;  
        int textExitX = buttonX + (buttonWidth - MeasureText("Exit", 25)) / 2;

        DrawRectangle(buttonX, 300, buttonWidth, buttonHeight, DARKGRAY);
        DrawText("Retry", textRetryX, 315, 25, WHITE);

        DrawRectangle(buttonX, 370, buttonWidth, buttonHeight, DARKGRAY);
        DrawText("Exit", textExitX, 385, 25, WHITE);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (mouse.x >= buttonX && mouse.x <= buttonX + buttonWidth) {
                if (mouse.y >= 300 && mouse.y <= 350) {
                    return true;
                }
                if (mouse.y >= 370 && mouse.y <= 420) {
                    return false;
                }
            }
        }
    }
    return false;
}