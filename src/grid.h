#pragma once
#include <array>
#include "cell.h"

class Grid {
public:
    explicit Grid(const CellState fill = CellState::Empty) : cells() {
        for (auto& row : cells) row.fill(fill);
    }

    CellState Get(const int x, const int y) const                          { return cells[y][x]; }
    void Set(const int x, const int y, const CellState s) {
        cells[y][x] = s;
    }

    void DrawRookAttack(const CellInfo info) {
        // Top to Bottom
        for (int x = info.x + 1; x < BoardSize; ++x) {
            Set(x, info.y, CellState::Attack);
        }
        for (int x = info.x - 1; x >= 0; --x) {
            Set(x, info.y, CellState::Attack);
        }

        // Left to Right
        for (int y = info.y + 1; y < BoardSize; ++y) {
            Set(info.x, y, CellState::Attack);
        }
        for (int y = info.y - 1; y >= 0; --y) {
            Set(info.x, y, CellState::Attack);
        }
    }

    void DrawHitMarkers() {
        for (int y = 0; y < BoardSize; ++y)
            for (int x = 0; x < BoardSize; ++x)
                if (cells[y][x] == CellState::Rook)
                    DrawRookAttack({CellState::Rook, x, y});
    }

    void DrawObjects() const {
        for (int y = 0; y < BoardSize; ++y)
            for (int x = 0; x < BoardSize; ++x)
                DrawCell(cells[y][x], x, y);
    }

    void Draw() {
        DrawObjects();
        DrawHitMarkers();
    }


    static bool InBounds(const int x, const int y) { return x >= 0 && x < BoardSize && y >= 0 && y < BoardSize; }

private:
    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
};