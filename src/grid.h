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

    void Draw() const {
        for (int y = 0; y < BoardSize; ++y)
            for (int x = 0; x < BoardSize; ++x)
                DrawCell(cells[y][x], x, y);
    }

    static bool InBounds(const int x, const int y) { return x >= 0 && x < BoardSize && y >= 0 && y < BoardSize; }

private:
    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
};