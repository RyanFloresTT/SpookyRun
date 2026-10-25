#pragma once
#include "save_manager.h"

class WebSaveManager : public SaveManager{
public:
    WebSaveManager();
    void SaveProgress(int unlocked) override;
    int LoadProgress() override;
};
