// level_menu.h
#pragma once
#include "lantern/scene/scene.h"

class LevelMenu : public Scene {
public:
    explicit LevelMenu(AssetStore& asset_store) : Scene(asset_store) {}
    void Enter() override;
    void Update(float) override;
    void Draw() override;

private:
    void draw_level_buttons();

    int level_count    = 0;
    int first_row      = 0;
    int unlocked_count = 1;
};
