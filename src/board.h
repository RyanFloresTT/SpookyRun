#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "cell.h"
#include "pieces/piece_factory.h"

class Board {
public:
    explicit Board(const CellState fill = CellState::Empty) {
        Reset(DefaultBoardSize, fill);
    }

    void Reset(int size, const CellState fill = CellState::Empty) {
        size += 2;
        if (size < 1 || size > TotalBoardWidth) {
            throw std::invalid_argument("Board size must fit the board viewport");
        }
        pendingRemovals.clear();
        pieces.clear();
        cells.assign(size, std::vector(size, fill));
        playerCaptured = false;
        player_reached_end = false;
    }

    int   GetSize() const { return static_cast<int>(cells.size()); }
    float GetTileSize() const { return static_cast<float>(TotalBoardWidth) / GetSize(); }
    bool  PlayerCaptured() const;
    bool  InBounds(const int x, const int y) const { return x >= 0 && x < GetSize() && y >= 0 && y < GetSize() && cells[y][x] != CellState::Border; }

    CellState get_cell_state(const int x, const int y) const { return cells[y][x]; }

    void set_cell_state(const int x, const int y, const CellState s) {
        cells[y][x] = s;
    }

    void AddPiece(const PieceType type, const int x, const int y, const std::vector<Vector2>& patrol_sequence) {
        if (!InBounds(x, y)) return;
        auto p = MakePiece(type, *this, x, y, patrol_sequence);
        if (!p) return;

        set_cell_state(x, y, CellState::Occupied);
        pieces.push_back(std::move(p));
        RefreshAttacks();
    }

    void RemovePieceAt(int x, int y) {
        if (!InBounds(x, y)) return;

        const auto it = std::ranges::find_if(pieces, [&](const auto& p) {
            const auto info = p->GetCellInfo();
            return info.x == x && info.y == y;
        });
        if (it == pieces.end()) return;

        pendingRemovals.push_back(it->get());
    }

    bool PieceTypeAt(PieceType type, float x, float y) const {
        for (auto& p : pieces) {
            if (p.get()->type != type) continue;
            const auto info = p->GetCellInfo();
            if (info.x == x && info.y == y) return true;
        }
        return false;
    }

    void NotifyPlayerMoved(const Piece* mover) const {
        for (auto& p : pieces) {
            if (p.get() != mover) p->DetectPlayer();
        }
        for (auto& p : pieces) {
            if (p.get() != mover && !p->IsAnimating() && !p->HasHitPlayer()) p->OnPlayerMoved();
        }
    }

    void RefreshAttacks() {
        ClearAttacks();
        for (const auto& p : pieces) p->SetHitSquares();
    }

    void draw_board_grid() const {
        const float tile_size = GetTileSize();

        for (int i = 1; i < DefaultBoardSize + 1; ++i) {
            for (int j = 1; j < DefaultBoardSize + 1; ++j){
                const Rectangle r = {i * tile_size, j * tile_size, tile_size, tile_size};
                DrawRectangleLinesEx(r, 1, BEIGE);
            }
        }
    }

    void Draw() const {
        for (int y = 0; y < GetSize(); ++y)
            for (int x = 0; x < GetSize(); ++x) {
                const CellState state = cells[y][x];
                if (state == CellState::Border) {
                    DrawBorderCell(x, y, GetTileSize(), GetSize());
                    continue;
                }
                DrawCell(state, x, y, GetTileSize());
            }

        draw_board_grid();

        for (auto& p : pieces) p->Draw();
    }

    bool ResolvingMoves() const {
        for (auto& piece : pieces) {
            if (piece->IsAnimating()) {
                return true;
            }
        }
        return false;
    }

    bool PlayerIsMoving() const {
        for (const auto& piece : pieces) {
            if (piece->type == PieceType::Pawn) return piece->IsAnimating();
        }
        return false;
    }

    void Update(const float dt) {
        for (auto& p : pieces) p->Update(dt);
        for (Piece* target : pendingRemovals) RemovePiece(target);
        pendingRemovals.clear();

        if (dirty) {
            RefreshAttacks();
            dirty = false;
        }

        for (auto& p : pieces)
            if (p->HasHitPlayer()) playerCaptured = true;
    }

    bool check_player_win() const { return player_won; }
    void set_player_won(const bool won) { player_won = won; }
    void Enter() {
        player_won = false;
        // set border states
        for (int i = 0; i < GetSize(); ++i) {
            // top and bottom
            set_cell_state(i, 0, CellState::Border);
            set_cell_state(i,  GetSize() - 1, CellState::Border);

            // left and right
            set_cell_state(0, i, CellState::Border);
            set_cell_state( GetSize() - 1, i, CellState::Border);
        }
    }

    bool PlayerWon() const {return player_reached_end; }
    void PlayerReachedEnd() { player_reached_end = true; }

private:
    void RemovePiece(Piece* target) {
        const auto info = target->GetCellInfo();
        set_cell_state(info.x, info.y, CellState::Empty);
        std::erase_if(pieces, [&](auto& p) { return p.get() == target; });
        dirty = true;
    }

    void ClearAttacks() {
        for (auto& row : cells)
            for (auto& cell : row)
                if (cell == CellState::Attack) cell = CellState::Empty;
    }

    std::vector<std::vector<CellState>> cells;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<Piece*>                 pendingRemovals;
    bool                                playerCaptured = false;
    bool                                dirty          = false;
    bool                                player_won     = false;
    bool                                player_reached_end = false;
};

inline bool Board::PlayerCaptured() const { return playerCaptured; }
