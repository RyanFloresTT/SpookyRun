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

    static void DrawRookAttack(CellInfo info) {
        // Top to Bottom
        for (int x = info.x + 1; x < BoardSize; ++x) {
            DrawCell(CellState::Attack, x, info.y);
        }
        for (int x = info.x - 1; x >= 0; --x) {
            DrawCell(CellState::Attack, x, info.y);
        }

        // Left to Right
        for (int y = info.y + 1; y < BoardSize; ++y) {
            DrawCell(CellState::Attack, info.x, y);
        }
        for (int y = info.y - 1; y >= 0; --y) {
            DrawCell(CellState::Attack, info.x, y);
        }
    }

    void DrawHitMarkers() const {
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

    void Draw() const {
        DrawObjects();
        DrawHitMarkers();
    }


    static bool InBounds(const int x, const int y) { return x >= 0 && x < BoardSize && y >= 0 && y < BoardSize; }

private:
    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
};