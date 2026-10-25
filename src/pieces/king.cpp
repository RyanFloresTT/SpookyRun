//
// Created by rryan on 10/24/2026.
//

#include "king.h"
#include "../board.h"

void King::SetHitSquares() {
    hit_squares.clear();

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            const int x = info.x + dx;
            const int y = info.y + dy;
            if (!game_board.InBounds(x, y)) continue;
            if (game_board.get_cell_state(x, y) == CellState::Occupied) continue;
            game_board.set_cell_state(x, y, CellState::Attack);
            hit_squares.push_back(Vector2(x, y));
        }
    }
}
