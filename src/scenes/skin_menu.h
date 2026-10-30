#pragma once
#include "lantern/scene/scene.h"

// Lets the player pick an alternate skin. The skin textures live in this scene's
// AssetStore, so they're only loaded while the menu is open.
class SkinMenu : public Scene {
public:
    void Update(float) override;
    void Draw() override;

private:
    void draw_skin_buttons();

    int first_row = 0;
};
