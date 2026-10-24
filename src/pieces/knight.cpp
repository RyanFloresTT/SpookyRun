//
// Created by rryan on 10/24/2026.
//

#include "knight.h"
#include "../board.h"

void Knight::SetHitSquares() {
    struct Offset { int dx, dy; };
    constexpr Offset offsets[] = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    for (const auto& [dx, dy] : offsets) {
        const int x = info.x + dx;
        const int y = info.y + dy;
        if (!Board::InBounds(x, y)) continue;
        if (game_board.Get(x, y) == CellState::Occupied) continue; // knights jump, so only skip this square
        game_board.Set(x, y, CellState::Attack);
    }
}

void Knight::DetectPlayer() {}
