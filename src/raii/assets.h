#pragma once
#include <map>
#include <ranges>
#include <string>

#include "raylib.h"
#include "../pieces/piece_type.h"

template <typename T>
struct asset_info {
    T asset;
    std::string path;
};

class AssetManager {
public:
    static void load_assets() {
        // Textures
        for (auto& [texture, path] : textures | std::views::values) {
            texture = LoadTexture(path.c_str());
        }

        // Font
        font.asset = LoadFont(font.path.c_str());

        // Cursor
        cursor.asset = LoadTexture(cursor.path.c_str());

        // SFX
    }

    static void unload_assets() {
        for (auto& [texture, path] : textures | std::views::values) {
            UnloadTexture(texture);
        }
    }

    static Texture2D& GetTexture(const PieceType name) { return textures.at(name).asset; }
    static Font& GetFont() { return font.asset; }
    static Texture2D& GetCursor() { return cursor.asset; }

private:
    static inline std::map<PieceType, asset_info<Texture2D>> textures = {
        {PieceType::Rook, {{}, "assets/images/rook.png"}},
        {PieceType::Pawn, {{}, "assets/images/pawn.png"}},
        {PieceType::Bishop, {{}, "assets/images/bishop.png"}},
        {PieceType::Queen, {{}, "assets/images/queen.png"}},
        {PieceType::King, {{}, "assets/images/king.png"}},
        {PieceType::Knight, {{}, "assets/images/knight.png"}},
    };

    static inline asset_info<Font> font = {{}, "assets/font/supply-center.regular.ttf"};
    static inline asset_info<Texture2D> cursor = {{}, "assets/cursor/hand_small_point.png"};
};