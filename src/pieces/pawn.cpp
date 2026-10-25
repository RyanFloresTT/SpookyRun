//
// Created by rryan on 10/23/2026.
//

#include "pawn.h"

#include <cmath>

#include "../board.h"
#include "../scenes/scene_manager.h"
#include "../scenes/win_scene.h"

void Pawn::SetHitSquares() {
    /* no op */
}

bool Pawn::validate_pawn_move(const int       target_x, const int target_y, const int dx, const int dy,
                              const CellState destination_state) const {
    const int xMag = std::abs(dx);

    if (xMag > 1 || std::abs(dy) > 1) return false;             // can't move more than one spot
    if (target_x == info.x && target_y == info.y) return false; // can't move to its current spot
    if (xMag >= 1 && dy == 0) return false;                     // can't move left to right

    if (xMag > 0 && dy < 0) {
        // can only go diagonal to attack
        if (destination_state != CellState::Occupied) return false;
    }

    if (xMag > 0 && dy >= 1) {
        // can only go backwards diagonally if there is something there
        if (destination_state == CellState::Occupied) return true;
        return false;
    }

    return true;
}

void Pawn::Move(const int target_x, const int target_y) {
    if (is_moving) return;
    if (!game_board.InBounds(target_x, target_y)) return;

    const int dx = target_x - info.x;
    const int dy = target_y - info.y;

    const CellState destinationState = game_board.get_cell_state(target_x, target_y);

    if (!validate_pawn_move(target_x, target_y, dx, dy, destinationState)) return;

    if (destinationState == CellState::Occupied) {
        game_board.RemovePieceAt(target_x, target_y);
    }

    game_board.set_cell_state(info.x, info.y, CellState::Empty);

    MoveTo(target_x, target_y);
    game_board.set_cell_state(target_x, target_y, CellState::Occupied);
    game_board.NotifyPlayerMoved(this);
}

void Pawn::Update(const float dt) {
    Piece::Update(dt);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        const float tile_size = game_board.GetTileSize();
        Move(static_cast<int>(std::floor(GetMouseX() / tile_size)),
             static_cast<int>(std::floor(GetMouseY() / tile_size)));
    }

    if (PlayerWon()) {
        game_board.set_player_won(true);
    }
}

void Pawn::Init() const {
    game_board.set_cell_state(info.x, info.y, CellState::Occupied);
}

bool Pawn::PlayerWon() const {
    return info.y == 0 && !is_moving;
}
