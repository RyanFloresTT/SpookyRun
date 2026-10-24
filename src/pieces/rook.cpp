#include "rook.h"

#include "../board.h"

void Rook::SetHitSquares() {
    struct Dir { int dx, dy; };
    constexpr Dir dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& [dx, dy] : dirs) {
        for (int x = info.x + dx, y = info.y + dy;
             Board::InBounds(x, y);
             x += dx, y += dy) {
            if (PlayableGrid.Get(x, y) == CellState::Occupied) break;
            PlayableGrid.Set(x, y, CellState::Attack);}
    }
}

void Rook::Update(float dt) {}
