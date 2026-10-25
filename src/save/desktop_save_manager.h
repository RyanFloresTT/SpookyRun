#pragma once
#include "save_manager.h"

class DesktopSaveManager : public SaveManager{
public:
    DesktopSaveManager();
    void SaveProgress(int unlocked) override;
    int LoadProgress() override;
};
