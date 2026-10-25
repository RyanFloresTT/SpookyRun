#pragma once
#include "../raii/assets.h"

enum class PieceType { Rook, Pawn, Bishop, Knight, Queen, King };

inline TextureAssets ToTextureAsset(const PieceType piece) {
    switch (piece) {
    case PieceType::Rook: return TextureAssets::Rook;
    case PieceType::Pawn: return TextureAssets::Pawn;
    case PieceType::Bishop: return TextureAssets::Bishop;
    case PieceType::Knight: return TextureAssets::Knight;
    case PieceType::Queen: return TextureAssets::Queen;
    case PieceType::King: return TextureAssets::King;
    default: return TextureAssets::Rook;
    }
}
