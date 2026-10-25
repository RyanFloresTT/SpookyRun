#include "piece_factory.h"

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece_type.h"
#include "queen.h"
#include "rook.h"

std::unique_ptr<Piece> MakePiece(const PieceType type, Board& grid, int x, int y, const std::vector<Vector2>& patrol_sequence) {
    switch (type) {
    case PieceType::Rook:   return std::make_unique<Rook>(grid, x, y, patrol_sequence);
    case PieceType::Pawn:   return std::make_unique<Pawn>(x, y, grid);
    case PieceType::Bishop: return std::make_unique<Bishop>(grid, x, y, patrol_sequence);
    case PieceType::Knight: return std::make_unique<Knight>(grid, x, y, patrol_sequence);
    case PieceType::King:   return std::make_unique<King>(grid, x, y, patrol_sequence);
    case PieceType::Queen:  return std::make_unique<Queen>(grid, x, y, patrol_sequence);
    default:              return nullptr;
    }
}
