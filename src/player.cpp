//
// Created by rryan on 10/23/2026.
//

#include "player.h"

#include <cmath>

#include "grid.h"

void Player::Move(const int dx, const int dy) {
    // Make sure player moves within bounds, not on something, and not more than one space ahead
    // Will revisit this so pawn can't move backwards (if that's what I want still)
    if (!Grid::InBounds(dx, dy)) return;
    if (PlayableGrid.Get(dx, dy) != CellState::Empty) return;
    if (std::abs(dx - x) > 1 || std::abs(dy - y) > 1) return;

    PlayableGrid.Set(dx, dy, CellState::Pawn);
    PlayableGrid.Set(x, y, CellState::Empty);

    x = dx;
    y = dy;
}

void Player::Init() const {
    PlayableGrid.Set(x, y, CellState::Pawn);
}

bool Player::PlayerWon() const {
    return y == 0;
}
