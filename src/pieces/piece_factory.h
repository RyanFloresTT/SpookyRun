#pragma once
#include <memory>
#include "piece.h"
#include "piece_type.h"

class Board;
std::unique_ptr<Piece> MakePiece(PieceType                   type, Board& grid, int x, int y,
                                 const std::vector<Vector2>& patrol_sequence = {});
