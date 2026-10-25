#pragma once
#include <map>
#include <ranges>
#include <string>

#include "raylib.h"

template <typename T>
struct asset_info {
    T           asset;
    std::string path;
};

enum class TextureAssets {
    Rook, Pawn, Bishop, Queen, King, Knight,
    ButtonBackground, RepeatIcon,
    Cursor, Star,
    WhiteFloor2, BlackFloor1,
};

enum class FontAssets {
    SupplyCenter
};

enum class SFXAssets {
    ButtonClick,
    PawnMove
};

enum class MusicAssets {
    Seaside
};

// Class is a little cleaner, but still can be worked on, will do for now
class AssetManager {
public:
    static void load_assets() {
        // Textures
        for (auto& [texture, path] : textures | std::views::values) {
            texture = LoadTexture(path.c_str());
        }

        // Font
        for (auto& [font, path] : fonts | std::views::values) {
            font = LoadFont(path.c_str());
        }

        // SFX
        for (auto& [sfx, path] : sounds | std::views::values) {
            sfx = LoadSound(path.c_str());
        }

        // Music
        for (auto& [music, path] : music_tracks | std::views::values) {
            music = LoadMusicStream(path.c_str());
        }
    }

    static void unload_assets() {
        // Textures
        for (auto& [texture, path] : textures | std::views::values) {
            UnloadTexture(texture);
        }

        // Font
        for (auto& [font, path] : fonts | std::views::values) {
            UnloadFont(font);
        }

        // SFX
        for (auto& [sfx, path] : sounds | std::views::values) {
            UnloadSound(sfx);
        }

        // Music
        for (auto& [music, path] : music_tracks | std::views::values) {
            UnloadMusicStream(music);
        }

        // Move out
        CloseAudioDevice();
    }

    static Texture2D& Get(const TextureAssets key) { return textures.at(key).asset; }
    static Font&      Get(const FontAssets key) { return fonts.at(key).asset; }
    static Sound&     Get(const SFXAssets key) { return sounds.at(key).asset; }
    static Music&     Get(const MusicAssets key) { return music_tracks.at(key).asset; }

private:
    static inline std::map<TextureAssets, asset_info<Texture2D>> textures = {
        {TextureAssets::Rook, {{}, "assets/images/rook.png"}},
        {TextureAssets::Pawn, {{}, "assets/images/player1.png"}},
        {TextureAssets::Bishop, {{}, "assets/images/bishop.png"}},
        {TextureAssets::Queen, {{}, "assets/images/queen.png"}},
        {TextureAssets::King, {{}, "assets/images/king.png"}},
        {TextureAssets::Knight, {{}, "assets/images/knight.png"}},


        {TextureAssets::Star, {{}, "assets/images/star.png"}},

        {TextureAssets::ButtonBackground, {{}, "assets/ui/button_bg.png"}},
        {TextureAssets::RepeatIcon, {{}, "assets/ui/icon_repeat_outline.png"}},
        {TextureAssets::Star, {{}, "assets/images/star.png"}},

        {TextureAssets::WhiteFloor2, {{}, "assets/images/white_floors/floor2.png"}},
        {TextureAssets::BlackFloor1, {{}, "assets/images/black_floors/floor1.png"}},

        {TextureAssets::Cursor, {{}, "assets/cursor/hand_small_point.png"}},

    };

    static inline std::map<FontAssets, asset_info<Font>> fonts = {
        {FontAssets::SupplyCenter, {{}, "assets/font/supply-center.regular.ttf"}}
    };
    static inline std::map<SFXAssets, asset_info<Sound>> sounds = {
        {SFXAssets::ButtonClick, {{}, "assets/sfx/button_click.wav"}},
        {SFXAssets::PawnMove, {{}, "assets/sfx/footstep_concrete_003.wav"}}
    };
    static inline std::map<MusicAssets, asset_info<Music>> music_tracks = {
        {MusicAssets::Seaside, {{}, "assets/music/Week 26 - Seaside ENDLESS WAVES.ogg"}}
    };
};
