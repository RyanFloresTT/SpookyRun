//
// Created by rryan on 10/24/2026.
//

#include "queen.h"
#include "../board.h"

void Queen::SetHitSquares() {
    struct Dir { int dx, dy; };
    constexpr Dir dirs[] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (const auto& [dx, dy] : dirs) {
        for (int x = info.x + dx, y = info.y + dy;
             Board::InBounds(x, y);
             x += dx, y += dy) {
            if (game_board.Get(x, y) == CellState::Occupied) break;
            game_board.Set(x, y, CellState::Attack);
             }
    }
}
