#pragma once
#include "lantern/scene/scene.h"

class LostScene : public Scene {
public:
    LostScene(AssetStore& asset_store, const int retryLevel) : Scene(asset_store), retry_level(retryLevel) {}

    void Update(float) override {}
    void Draw() override;

private:
    int   retry_level;
};
