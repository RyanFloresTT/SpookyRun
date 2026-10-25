//
// Created by rryan on 10/24/2026.
//
#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include "raylib.h"
#include "../board.h"
#ifdef __EMSCRIPTEN__
#include "../save/web_save_manager.h"
#else
#include "../save/desktop_save_manager.h"
#endif

using json = nlohmann::json;

class LevelManager {
public:
    static int GetLevelCount() {
        std::ifstream file("assets/levels/levels.json");
        if (!file) {
            TraceLog(LOG_ERROR, "Could not open levels.json");
            return 0;
        }

        const json data = json::parse(file, nullptr, false);
        if (data.is_discarded() || !data.is_object() ||
            !data.contains("levels") || !data["levels"].is_object()) {
            TraceLog(LOG_ERROR, "levels.json must contain a levels object");
            return 0;
        }

        return static_cast<int>(data["levels"].size());
    }

    static void LoadLevel(const int level, Board& board) {
        std::ifstream file("assets/levels/levels.json");
        if (!file) {
            TraceLog(LOG_ERROR, "Could not open levels.json");
            return;
        }

        const json data = json::parse(file, nullptr, false);
        if (data.is_discarded()) {
            TraceLog(LOG_ERROR, "levels.json is not valid JSON");
            return;
        }

        const std::string key = std::to_string(level);
        if (!data["levels"].contains(key)) {
            TraceLog(LOG_ERROR, "No level %d in levels.json", level);
            return;
        }

        const json& lvl = data["levels"][key];

        const json size = lvl.value("size", json(DefaultBoardSize));
        if (!size.is_number_integer() || size < 1 || size > TotalBoardWidth) {
            TraceLog(LOG_ERROR, "Level %d size must be an integer between 1 and %d", level, TotalBoardWidth);
            return;
        }
        board.Reset(size.get<int>());

        for (const auto& p : lvl["pieces"]) {
            const std::string type = p.value("type", "");
            const int         x    = p.value("x", 0);
            const int         y    = p.value("y", 0);

            const auto it = pieceNames.find(type);
            if (it == pieceNames.end()) {
                TraceLog(LOG_WARNING, "Unknown piece type '%s'", type.c_str());
                continue;
            }
            if (!board.InBounds(x, y)) {
                TraceLog(LOG_WARNING, "Piece '%s' out of bounds (%d, %d)", type.c_str(), x, y);
                continue;
            }

            std::vector<Vector2> patrol;
            if (p.contains("patrol_sequence")) {
                if (!p["patrol_sequence"].is_array()) {
                    TraceLog(LOG_WARNING, "Level %d: patrol_sequence on '%s' must be an array", level, type.c_str());
                }
                else {
                    for (const auto& step : p["patrol_sequence"]) {
                        patrol.push_back(Vector2(step.value("x", 0), step.value("y", 0)));
                    }
                }
            }

            board.AddPiece(it->second, x, y, patrol);
        }
    }

    static void SaveProgress(const int level) {
        GetSaveManager().SaveProgress(level);
    }

    static int LoadProgress() {
        return GetSaveManager().LoadProgress();
    }

private:
    static SaveManager& GetSaveManager() {
        static std::unique_ptr<SaveManager> instance =
#ifndef __EMSCRIPTEN__
                std::make_unique<DesktopSaveManager>();
#else
                std::make_unique<WebSaveManager>();
#endif
        return *instance;
    }

    static inline std::unordered_map<std::string, PieceType> pieceNames = {
        {"Pawn", PieceType::Pawn}, {"Rook", PieceType::Rook},
        {"Bishop", PieceType::Bishop}, {"Knight", PieceType::Knight},
        {"Queen", PieceType::Queen}, {"King", PieceType::King},
    };
};


