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
    Rook, Player, Bishop, Queen, King, Knight,
    ButtonBackground, RepeatIcon,
    Cursor, Star,
    WhiteFloor2, BlackFloor1,
    MenuBackground, RoundButton, CrossIcon, WhiteButton, Sword, MenuButton
};

enum class AlternateSkinAssets {
    Monk, Barb, GWizard,
    BWizard, Armor, ArmorNoHelm,
    ArmorOpen, Chef, Dude,
    Lady, OldLady, Viking
};

enum class FontAssets {
    SupplyCenter
};

enum class SFXAssets {
    ButtonClick,
    PawnMove, ArrowButtonClick
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
        
        for (auto& [texture, path] : alternate_skins | std::views::values) {
            texture = LoadTexture(path.c_str());
        }

        // Font
        for (auto& [font, path] : fonts | std::views::values) {
            font = LoadFontEx(path.c_str(), 96, nullptr, 0);
            SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
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

        for (auto& [texture, path] : alternate_skins | std::views::values) {
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
    static const Texture2D& Get(const AlternateSkinAssets skin) { return alternate_skins.at(skin).asset; }
    static std::string& GetPath(const TextureAssets key) { return textures.at(key).path; }
    static Font&      Get(const FontAssets key) { return fonts.at(key).asset; }
    static Sound&     Get(const SFXAssets key) { return sounds.at(key).asset; }
    static Music&     Get(const MusicAssets key) { return music_tracks.at(key).asset; }

    static int GetAlternateSkinCount() { return static_cast<int>(alternate_skins.size()); }
    static std::string& GetAlternateSkinPath(const AlternateSkinAssets key) { return alternate_skins.at(key).path; }
    static AlternateSkinAssets GetAlternateSkinKey(const int index) {
        return std::next(alternate_skins.begin(), index)->first;
    }

    static void SwapTexturePath(const TextureAssets key, const std::string& newPath) {
        UnloadTexture(textures.at(key).asset);
        LoadTexture(newPath.c_str());
    }

    static void SwapPlayerSkin(const AlternateSkinAssets skin) {
        UnloadTexture(textures.at(TextureAssets::Player).asset);
        LoadTexture(GetAlternateSkinPath(skin).c_str());
    }

    static inline std::map<AlternateSkinAssets, asset_info<Texture2D>> alternate_skins = {
        {AlternateSkinAssets::Armor, {{}, "assets/images/armor.png"}},
        {AlternateSkinAssets::ArmorNoHelm, {{}, "assets/images/armor_nohelm.png"}},
        {AlternateSkinAssets::ArmorOpen, {{}, "assets/images/armor_open.png"}},
        {AlternateSkinAssets::BWizard, {{}, "assets/images/b_wizard.png"}},
        {AlternateSkinAssets::Barb, {{}, "assets/images/barb.png"}},
        {AlternateSkinAssets::Chef, {{}, "assets/images/chef.png"}},
        {AlternateSkinAssets::Dude, {{}, "assets/images/dude.png"}},
        {AlternateSkinAssets::GWizard, {{}, "assets/images/g_wizard.png"}},
        {AlternateSkinAssets::Lady, {{}, "assets/images/lady.png"}},
        {AlternateSkinAssets::Monk, {{}, "assets/images/monk.png"}},
        {AlternateSkinAssets::OldLady, {{}, "assets/images/old_lady.png"}},
        {AlternateSkinAssets::Viking, {{}, "assets/images/viking.png"}},
    };

private:
    static inline std::map<TextureAssets, asset_info<Texture2D>> textures = {
        {TextureAssets::Rook, {{}, "assets/images/rook.png"}},
        {TextureAssets::Player, {{}, "assets/images/monk.png"}},
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

        {TextureAssets::MenuBackground, {{}, "assets/ui/button_rectangle_depth_line.png"}},
        {TextureAssets::RoundButton, {{}, "assets/ui/button_round_line.png"}},
        {TextureAssets::CrossIcon, {{}, "assets/ui/icon_cross.png"}},
        {TextureAssets::WhiteButton, {{}, "assets/ui/button_square_depth_line.png"}},
        {TextureAssets::Sword, {{}, "assets/ui/tile_0103.png"}},
        {TextureAssets::MenuButton, {{}, "assets/ui/button_rectangle_depth_border.png"}},
    };

    static inline std::map<FontAssets, asset_info<Font>> fonts = {
        {FontAssets::SupplyCenter, {{}, "assets/font/supply-center.regular.ttf"}}
    };
    static inline std::map<SFXAssets, asset_info<Sound>> sounds = {
        {SFXAssets::ButtonClick, {{}, "assets/sfx/button_click.wav"}},
        {SFXAssets::PawnMove, {{}, "assets/sfx/footstep_concrete_003.wav"}},
        {SFXAssets::ArrowButtonClick, {{}, "assets/sfx/tap-a.ogg"}}
    };
    static inline std::map<MusicAssets, asset_info<Music>> music_tracks = {
        {MusicAssets::Seaside, {{}, "assets/music/Week 26 - Seaside ENDLESS WAVES.ogg"}}
    };
};
