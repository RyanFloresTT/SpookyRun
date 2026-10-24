#pragma once
#include <map>
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
        for (auto& [name, info] : textures) {
            info.texture = LoadTexture(info.path.c_str());
        }
    }

    static void UnloadTextures() {
        for (auto& [name, info] : textures) {
            UnloadTexture(info.texture);
        }
    }

    static Texture2D& GetTexture(const PieceType name) { return textures.at(name).texture; }

private:
    static inline std::map<PieceType, TextureInfo> textures = {
        {PieceType::Rook, {{}, "assets/rook.png"}},
        {PieceType::Pawn, {{}, "assets/pawn.png"}},
    };
};