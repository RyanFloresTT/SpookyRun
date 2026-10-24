//
// Created by rryan on 10/24/2026.
//

#include "king.h"
#include "../board.h"

void King::SetHitSquares() {
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            const int x = info.x + dx;
            const int y = info.y + dy;
            if (!Board::InBounds(x, y)) continue;
            if (game_board.Get(x, y) == CellState::Occupied) continue;
            game_board.Set(x, y, CellState::Attack);
        }
    }
}

void King::DetectPlayer() {}
