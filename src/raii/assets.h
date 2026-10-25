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

enum class TextureAssets {
    Rook, Pawn, Bishop, Queen, King, Knight
};

enum class FontAssets {
    SupplyCenter
};

enum class SFXAssets {
    ButtonClick
};

enum class MusicAssets {
    Seaside
};

// could prob gather each by type somehow, load them, and unload them all at once
// the more I add to this, the more I want to refactor this...
class AssetManager {
public:
    static void load_assets() {
        // Textures
        for (auto& [texture, path] : textures | std::views::values) {
            texture = LoadTexture(path.c_str());
        }
        star.asset = LoadTexture("assets/images/star.png");

        // Font
        font.asset = LoadFont(font.path.c_str());

        // Cursor
        cursor.asset = LoadTexture(cursor.path.c_str());

        // SFX
        InitAudioDevice();
        button_click_sound.asset = LoadSound(button_click_sound.path.c_str());
        music.asset = LoadMusicStream(music.path.c_str());
        SetMusicVolume(music.asset, 0.2f);
    }

    static void unload_assets() {
        for (auto& [texture, path] : textures | std::views::values) {
            UnloadTexture(texture);
        }

        UnloadTexture(star.asset);
        UnloadFont(font.asset);
        UnloadTexture(cursor.asset);
        UnloadSound(button_click_sound.asset);
        UnloadMusicStream(music.asset);
        CloseAudioDevice();
    }

    static Texture2D& GetTexture(const PieceType name) { return textures.at(name).asset; }
    static Font& GetFont() { return font.asset; }
    static Texture2D& GetCursor() { return cursor.asset; }
    // will want to return more than just the button click
    static Sound& GetSound() {
        return button_click_sound.asset;
    }
    static void PlayMusic() {
        if (IsMusicStreamPlaying(music.asset)) return;
        PlayMusicStream(music.asset);
    };

    static void UpdateMusic() { UpdateMusicStream(music.asset); }
    static Texture2D& GetStar() { return star.asset; }

private:
    static inline std::map<PieceType, asset_info<Texture2D>> textures = {
        {PieceType::Rook,   {{}, "assets/images/rook.png"}},
        {PieceType::Pawn,   {{}, "assets/images/pawn.png"}},
        {PieceType::Bishop, {{}, "assets/images/bishop.png"}},
        {PieceType::Queen,  {{}, "assets/images/queen.png"}},
        {PieceType::King,   {{}, "assets/images/king.png"}},
        {PieceType::Knight, {{}, "assets/images/knight.png"}},
    };

    static inline asset_info<Font> font = {{}, "assets/font/supply-center.regular.ttf"};
    static inline asset_info<Texture2D> cursor = {{}, "assets/cursor/hand_small_point.png"};
    static inline asset_info<Sound> button_click_sound = {{}, "assets/sfx/button_click.wav"};
    static inline asset_info<Music> music = {{}, "assets/music/Week 26 - Seaside ENDLESS WAVES.ogg"};
    static inline asset_info<Texture2D> star = {{}, "assets/images/star.png"};
};