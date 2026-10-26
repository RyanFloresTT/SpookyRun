#pragma once
#include "save_manager.h"

class WebSaveManager : public SaveManager {
public:
    void SaveProgress(int unlocked) override;
    int LoadProgress() override;

private:
    int unlocked_progress = 1;
};
