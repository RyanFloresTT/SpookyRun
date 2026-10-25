//
// Created by rryan on 10/24/2026.
//

#include "bishop.h"
#include "../board.h"

void Bishop::SetHitSquares() {
    hit_squares.clear();

    struct Dir {
        int dx, dy;
    };
    constexpr Dir dirs[] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (const auto& [dx, dy] : dirs) {
        for (int x = info.x + dx, y = info.y + dy; game_board.InBounds(x, y); x += dx, y += dy) {
            hit_squares.push_back(Vector2(x, y));
            if (game_board.get_cell_state(x, y) == CellState::Occupied) break;
            game_board.set_cell_state(x, y, CellState::Attack);
        }
    }
}
