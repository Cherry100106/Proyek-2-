#include "farell.h"

void moveLeft(Block *block, Grid *grid) {
    // Cek collision sebelum bergerak
    for (int i = 0; i < 4; i++) {
        int newCol = block->cells[block->rotationState][i].column - 1;
        int row = block->cells[block->rotationState][i].row;
        if (newCol < 0 || grid->grid[row][newCol]) return;
    }
    // Geser blok ke kiri
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].column--;
    }
}

void moveRight(Block *block, Grid *grid) {
    // Cek collision sebelum bergerak
    for (int i = 0; i < 4; i++) {
        int newCol = block->cells[block->rotationState][i].column + 1;
        int row = block->cells[block->rotationState][i].row;
        if (newCol >= NUM_COLS || grid->grid[row][newCol]) return;
    }
    // Geser blok ke kanan
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].column++;
    }
}

void moveDown(Block *block, Grid *grid) {
    // Cek collision sebelum bergerak
    for (int i = 0; i < 4; i++) {
        int newRow = block->cells[block->rotationState][i].row + 1;
        int col = block->cells[block->rotationState][i].column;
        if (newRow >= NUM_ROWS || grid->grid[newRow][col]) return;
    }
    // Geser blok ke bawah
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].row++;
    }
}

void rotateBlock(Block *block, Grid *grid) {
    int nextRotation = (block->rotationState + 1) % 4; // Rotasi ke kanan

    // Tentukan titik pivot (misalnya, sel pertama blok)
    int pivotRow = block->cells[block->rotationState][0].row;
    int pivotCol = block->cells[block->rotationState][0].column;

    // Simpan posisi sel blok setelah rotasi
    Position tempCells[4];
    for (int i = 0; i < 4; i++) {
        tempCells[i].row = block->cells[nextRotation][i].row;
        tempCells[i].column = block->cells[nextRotation][i].column;
    }

    // Hitung offset untuk mempertahankan posisi blok di grid
    int offsetRow = pivotRow - tempCells[0].row;
    int offsetCol = pivotCol - tempCells[0].column;

    // Cek collision setelah rotasi dan offset
    for (int i = 0; i < 4; i++) {
        int row = tempCells[i].row + offsetRow;
        int col = tempCells[i].column + offsetCol;
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS || grid->grid[row][col]) {
            return; // Batalkan rotasi jika ada collision
        }
    }

    // Jika tidak ada collision, lakukan rotasi
    block->rotationState = nextRotation;

    // Perbarui posisi sel blok dengan offset
    for (int i = 0; i < 4; i++) {
        block->cells[block->rotationState][i].row = tempCells[i].row + offsetRow;
        block->cells[block->rotationState][i].column = tempCells[i].column + offsetCol;
    }
}