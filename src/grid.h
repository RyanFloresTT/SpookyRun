#pragma once
#include <vector>

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
    static Color GetCellColor(int x, int y);

private:
    size_t w, h;
    std::vector<T> cells;
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
            DrawRectangle(i * TileSize, j * TileSize, TileSize, TileSize, GetCellColor(i, j));
        }
    }
}