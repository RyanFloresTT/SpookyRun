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

    hit_squares.clear();

    for (const auto& [dx, dy] : offsets) {
        const int x = info.x + dx;
        const int y = info.y + dy;
        if (!game_board.InBounds(x, y)) continue;
        hit_squares.push_back(Vector2(x, y));
        if (game_board.get_cell_state(x, y) == CellState::Occupied) continue; // knights jump, so only skip this square
        game_board.set_cell_state(x, y, CellState::Attack);
    }
}
