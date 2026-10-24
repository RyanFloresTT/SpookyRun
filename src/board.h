#pragma once
#include <algorithm>
#include <array>
#include <vector>

#include "cell.h"
#include "pieces/piece_factory.h"

class Board {
public:
    explicit Board(const CellState fill = CellState::Empty) : cells() {
        for (auto& row : cells) row.fill(fill);
    }

    CellState Get(const int x, const int y) const { return cells[y][x]; }

    void Set(const int x, const int y, const CellState s) {
        cells[y][x] = s;
    }

    Piece* AddPiece(const PieceType type, const int x, const int y) {
        auto p = MakePiece(type, *this, x, y);
        if (!p) return nullptr;

        Piece* raw = p.get();
        Set(x, y, CellState::Occupied);
        pieces.push_back(std::move(p));
        RefreshAttacks();
        return raw;
    }

    void Draw() const {
        for (int y = 0; y < BoardSize; ++y)
            for (int x = 0; x < BoardSize; ++x)
                DrawCell(cells[y][x], x, y);

        for (auto& p : pieces) p->Draw();
    }

    void Update(const float dt) {
        for (auto& p : pieces) p->Update(dt);
        for (Piece* target : pendingRemovals) RemovePiece(target);
        pendingRemovals.clear();

        for (auto& p : pieces) {
            if (p->HasHitPlayer()) {
                playerCaptured = true;
            }
        }
    }

    void RemovePieceAt(int x, int y) {
        if (!InBounds(x, y)) return;

        const auto it = std::ranges::find_if(pieces, [&](const auto& p) {
            const auto info = p->GetCellInfo();
            return info.x == x && info.y == y;
        });
        if (it == pieces.end()) return;

        pendingRemovals.push_back(it->get());   // just queue it; don't move or erase yet
    }

    bool PieceTypeAt(PieceType type, float x, float y) const {
        for (auto& p : pieces) {
            if (p.get()->type != type) continue;
            const auto info = p->GetCellInfo();
            if (info.x == x && info.y == y) return true;
        }
        return false;
    }

    bool        PlayerCaptured() const;
    static bool InBounds(const int x, const int y) { return x >= 0 && x < BoardSize && y >= 0 && y < BoardSize; }

private:
    void RemovePiece(Piece* target) {
        const auto info = target->GetCellInfo();
        Set(info.x, info.y, CellState::Empty);
        std::erase_if(pieces, [&](auto& p) { return p.get() == target; });
        RefreshAttacks();
    }

    void RefreshAttacks() {
        ClearAttacks();
        for (const auto& p : pieces) p->SetHitSquares();
    }

    void ClearAttacks() {
        for (auto& row : cells)
            for (auto& cell : row)
                if (cell == CellState::Attack) cell = CellState::Empty;
    }

    std::array<std::array<CellState, BoardSize>, BoardSize> cells;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<Piece*> pendingRemovals;
    bool playerCaptured = false;
};

inline bool Board::PlayerCaptured() const { return playerCaptured; }
