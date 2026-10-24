#include "piece_factory.h"

#include "pawn.h"
#include "piece_type.h"
#include "rook.h"

std::unique_ptr<Piece> MakePiece(const PieceType type, Board& grid, int x, int y) {
    switch (type) {
    case PieceType::Rook: return std::make_unique<Rook>(grid, x, y);
    case PieceType::Pawn: return std::make_unique<Pawn>(x, y, grid);
    default:              return nullptr;
    }
}
