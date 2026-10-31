#pragma once
#include "lantern/scene/scene.h"

// Lets the player pick an alternate skin. Every skin texture lives in this scene's
// AssetScope, so they're only all loaded while the menu is open.
class SkinMenu : public Scene {
public:
    explicit SkinMenu(AssetStore& asset_store);

    void Update(float) override;
    void Draw() override;

private:
    void draw_skin_buttons();

    int first_row = 0;
};
