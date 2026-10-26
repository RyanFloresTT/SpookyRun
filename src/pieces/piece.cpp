//
// Created by rryan on 10/24/2026.
//
// src/pieces/piece.cpp
#include "piece.h"
#include "../board.h"

void Piece::Draw() const {
    float progress = is_moving ? animation_timer / move_duration : 1.0f;
    progress       = 1.0f - (1.0f - progress) * (1.0f - progress) * (1.0f - progress);

    const float tile_size = game_board.GetTileSize();
    const float px        = (from_x + (info.x - from_x) * progress) * tile_size;
    const float py        = (from_y + (info.y - from_y) * progress) * tile_size;
    DrawAsset(ToTextureAsset(type), px, py, tile_size);
}

void Piece::DetectPlayer() {
    if (type == PieceType::Pawn || is_moving || has_hit_player || game_board.PlayerWon() ||
        game_board.PlayerIsMoving()) return;

    for (const auto [x, y] : hit_squares) {
        if (game_board.PieceTypeAt(PieceType::Pawn, x, y)) {
            MoveTo(x, y);
            return;
        }
    }
}

void Piece::OnPlayerMoved() {
    if (patrol_sequence.empty()) return;

    MoveTo(info.x + patrol_sequence[current_patrol_index].x, info.y + patrol_sequence[current_patrol_index].y);
    current_patrol_index = (current_patrol_index + 1) % patrol_sequence.size();
}

void Piece::MoveTo(const int new_x, const int new_y) {
    if (game_board.PlayerWon()) return;
    if (!game_board.InBounds(new_x, new_y)) return;
    if (new_x == info.x && new_y == info.y) return;
    if (type != PieceType::Pawn) {
        if (game_board.get_cell_state(new_x, new_y) == CellState::Occupied &&
            !game_board.PieceTypeAt(PieceType::Pawn, new_x, new_y))
            return;
        game_board.set_cell_state(info.x, info.y, CellState::Empty);
        game_board.set_cell_state(new_x, new_y, CellState::Occupied);
    }
    hit_squares.clear();

    from_x = info.x;
    from_y = info.y;
    info.x = new_x;
    info.y = new_y;

    const auto  dx       = static_cast<float>(new_x - from_x);
    const auto  dy       = static_cast<float>(new_y - from_y);
    const float distance = std::sqrt(dx * dx + dy * dy); // in tiles

    move_duration   = distance * seconds_per_tile;
    animation_timer = 0.0f;
    is_moving       = true;
}

void Piece::OnMovementFinished() {
    PlaySound(AssetManager::Get(SFXAssets::PawnMove));
    if (type == PieceType::Pawn) return;

    if (game_board.PieceTypeAt(PieceType::Pawn, info.x, info.y)) {
        has_hit_player = true;
        return;
    }

    game_board.RefreshAttacks();
    DetectPlayer();
}
