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

    void Reset(const int size, const CellState fill = CellState::Empty) {
        if (size < 1 || size > TotalBoardWidth) {
            throw std::invalid_argument("Board size must fit the board viewport");
        }
        pendingRemovals.clear();
        pieces.clear();
        cells.assign(size, std::vector<CellState>(size, fill));
        playerCaptured = false;
    }

    int GetSize() const { return static_cast<int>(cells.size()); }
    float GetTileSize() const { return static_cast<float>(TotalBoardWidth) / GetSize(); }

    CellState Get(const int x, const int y) const { return cells[y][x]; }

    void Set(const int x, const int y, const CellState s) {
        cells[y][x] = s;
    }

    Piece* AddPiece(const PieceType type, const int x, const int y) {
        if (!InBounds(x, y)) return nullptr;
        auto p = MakePiece(type, *this, x, y);
        if (!p) return nullptr;

        Piece* raw = p.get();
        Set(x, y, CellState::Occupied);
        pieces.push_back(std::move(p));
        RefreshAttacks();
        return raw;
    }

    void Draw() const {
        for (int y = 0; y < GetSize(); ++y)
            for (int x = 0; x < GetSize(); ++x)
                DrawCell(cells[y][x], x, y, GetTileSize());

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
    bool InBounds(const int x, const int y) const { return x >= 0 && x < GetSize() && y >= 0 && y < GetSize(); }

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

    std::vector<std::vector<CellState>> cells;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<Piece*> pendingRemovals;
    bool playerCaptured = false;
};

inline bool Board::PlayerCaptured() const { return playerCaptured; }
