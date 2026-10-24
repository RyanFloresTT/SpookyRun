#pragma once
#include <map>
#include <ranges>
#include <string>

#include "raylib.h"
#include "../pieces/piece_type.h"

struct TextureInfo {
    Texture2D texture;
    std::string path;
};

class AssetManager {
public:
    static void LoadTextures() {
        for (auto& [texture, path] : textures | std::views::values) {
            texture = LoadTexture(path.c_str());
        }
    }

    static void UnloadTextures() {
        for (auto& [texture, path] : textures | std::views::values) {
            UnloadTexture(texture);
        }
    }

    static Texture2D& GetTexture(const PieceType name) { return textures.at(name).texture; }

private:
    static inline std::map<PieceType, TextureInfo> textures = {
        {PieceType::Rook, {{}, "assets/rook.png"}},
        {PieceType::Pawn, {{}, "assets/pawn.png"}},
    };
};