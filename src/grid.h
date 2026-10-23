#pragma once
#include <array>
#include "cell.h"

class Grid {
public:
    explicit Grid(const CellState fill = CellState::Empty) : cells() {
        for (auto& row : cells) row.fill(fill);
    }

    CellState Get(const int x, const int y) const        { return cells[y][x]; }
    void Set(int x, int y, CellState s)                  { cells[y][x] = s; }
    void SetPlayer(int x, int y) {
        cells[PlayerY][PlayerX] = CellState::Empty;
        PlayerX = x; PlayerY = y;
        cells[PlayerY][PlayerX] = CellState::Pawn;
    }

    void Draw() const {
        for (int y = 0; y < BoardSize; ++y)
            for (int x = 0; x < BoardSize; ++x)
                DrawCell(cells[y][x], x, y);
    }

private:
    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
    int PlayerX, PlayerY;
};