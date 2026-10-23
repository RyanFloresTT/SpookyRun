#pragma once
#include <map>
#include <string>

#include "raylib.h"

enum class Asset {
    Rook,
    Pawn,
};

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

    static Texture2D& GetTexture(const Asset name) { return textures.at(name).texture; }

private:
    static inline std::map<Asset, TextureInfo> textures = {
        {Asset::Rook, {{}, "assets/rook.png"}},
        {Asset::Pawn, {{}, "assets/pawn.png"}},
    };
};