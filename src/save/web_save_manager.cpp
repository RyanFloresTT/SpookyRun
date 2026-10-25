//
// Created by rryan on 10/25/2026.
//

#include "save_manager.h"

class WebSaveManager : public SaveManager {
public:
    virtual ~WebSaveManager() = default;

    void Save() override {}
    void Load() override {}
};