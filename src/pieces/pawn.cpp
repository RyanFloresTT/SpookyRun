//
// Created by rryan on 10/23/2026.
//

#include "pawn.h"

#include <cmath>

#include "../board.h"
#include "../scenes/scene_manager.h"

void Pawn::SetHitSquares() { /* no op */ }

void Pawn::Move(const int dx, const int dy) {
    // Make sure player moves within bounds, not on something, and not more than one space ahead
    // Will revisit this so pawn can't move backwards (if that's what I want still)
    if (!Board::InBounds(dx, dy)) return;

    const CellState destinationState = PlayableGrid.Get(dx, dy);

    if (std::abs(dx - info.x) > 1 || std::abs(dy - info.y) > 1) return;

    if (dx == info.x && dy == info.y) return;

    if (destinationState == CellState::Occupied) {
        PlayableGrid.RemovePieceAt(dx, dy);
    }

    if (destinationState == CellState::Attack) {
        SceneManager::Get().GoTo(SceneType::Lose);
    }

    PlayableGrid.Set(dx, dy, CellState::Occupied);
    PlayableGrid.Set(info.x, info.y, CellState::Empty);

    info.x = dx;
    info.y = dy;
}

void Pawn::Update(float dt) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        Move(GetMouseX() / TileSize, GetMouseY() / TileSize);

    if (PlayerWon()) {
        SceneManager::Get().GoTo(SceneType::Win);
    }
}

void Pawn::Init() const {
    PlayableGrid.Set(info.x, info.y, CellState::Occupied);
}

bool Pawn::PlayerWon() const {
    return info.y == 0;
}