#pragma once

enum class PieceType { Rook, Pawn, Bishop, Knight, Queen, King };

inline std::string_view GetTexturePath(const PieceType piece) {
    switch (piece) {
    case PieceType::Rook: return Assets::Images::ROOK;
    case PieceType::Pawn: return Assets::Images::MONK;
    case PieceType::Bishop: return Assets::Images::BISHOP;
    case PieceType::Knight: return Assets::Images::KNIGHT;
    case PieceType::Queen: return Assets::Images::QUEEN;
    case PieceType::King: return Assets::Images::KING;
    default: return Assets::Images::ROOK;
    }
}
