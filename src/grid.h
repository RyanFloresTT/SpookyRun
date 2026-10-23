#pragma once
#include <array>

#include "config.h"
#include "raylib.h"
enum class CellState {
    Empty,
    Pawn,
    King
};

template <typename T>
class Grid {
public:
    Grid(const size_t width, const size_t height, const T& fill = CellState::Empty) : w {width}, h {height}, cells {fill} {}

    void         Draw() const;
    void         SetCell(int x, int y, const T& value);
    static Color GetCellColor(int x, int y);

private:
    size_t w, h;
    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
};

template <typename T>
Color Grid<T>::GetCellColor(int x, int y) {
    if ((x + y) % 2 == 0) {
        return MAROON;
    } else {
        return DARKGRAY;
    }}

template <typename T>
void Grid<T>::Draw() const {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (cells[i][j] == CellState::Empty) {
                DrawRectangle(i * TileSize, j * TileSize, TileSize, TileSize, GetCellColor(i, j));
            }
            if (cells[i][j] == CellState::Pawn) {
                DrawRectangle(i * TileSize, j * TileSize, TileSize, TileSize, GRAY);
            }

            if (cells[i][j] == CellState::King) {
                DrawRectangle(i * TileSize, j * TileSize, TileSize, TileSize, RED);
            }
        }
    }
}

template <typename T>
void Grid<T>::SetCell(int x, int y, const T& value) {
    cells[x][y] = value;
}
