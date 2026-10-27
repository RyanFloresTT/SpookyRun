#pragma once
#include "lantern/scene/scene.h"

class LostScene : public Scene {
public:
    explicit LostScene(const int retryLevel) : retry_level(retryLevel) {}

    void Update(float) override {}
    void Draw() override;

private:
    int   retry_level;
};
