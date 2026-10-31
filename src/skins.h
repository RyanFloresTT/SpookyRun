#pragma once

#include <array>
#include <string_view>

#include "assets.h"

namespace Skins {
    inline constexpr std::array<std::string_view, 12> All = {
        Assets::Images::MONK,  Assets::Images::BARB,         Assets::Images::G_WIZARD,
        Assets::Images::B_WIZARD, Assets::Images::ARMOR,     Assets::Images::ARMOR_NOHELM,
        Assets::Images::ARMOR_OPEN, Assets::Images::CHEF,    Assets::Images::DUDE,
        Assets::Images::LADY,  Assets::Images::OLD_LADY,     Assets::Images::VIKING,
    };

    // The player's chosen skin. Scenes load it into their own AssetScope when they draw the player.
    inline std::string_view Selected = Assets::Images::MONK;
}
