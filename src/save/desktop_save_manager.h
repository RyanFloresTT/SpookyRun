#pragma once
#include "save_manager.h"

class DesktopSaveManager : public SaveManager{
public:
    void SaveProgress(int unlocked) override;
    int LoadProgress() override;
};
