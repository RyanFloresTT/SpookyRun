//
// Created by rryan on 10/23/2026.
//

#include "grid.h"

#include "raylib.h"

Color GetCellColor(int x, int y) {
    if ((x + y) % 2 == 0) {
        return MAROON;
    } else {
        return DARKGRAY;
    }
}

void Grid::Draw() const {
    for (int i = 0; i < CellCountWidth; i++) {
        for (int j = 0; j < CellCountWidth; j++) {
            DrawRectangle(i * CellSize, j * CellSize, CellSize, CellSize, GetCellColor(i, j));
        }
    }
}

