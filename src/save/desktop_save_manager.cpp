//
// Created by rryan on 10/25/2026.
//

#include "save_manager.h"

class DesktopSaveManager : public SaveManager {
public:
    virtual ~DesktopSaveManager() = default;

    void Save() override {}
    void Load() override {}
};