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

using json = nlohmann::json;

class LevelManager {
public:
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

        for (const auto& p : lvl["pieces"]) {
            const std::string type = p.value("type", "");
            const int x = p.value("x", 0);
            const int y = p.value("y", 0);

            const auto it = pieceNames.find(type);
            if (it == pieceNames.end()) {
                TraceLog(LOG_WARNING, "Unknown piece type '%s'", type.c_str());
                continue;
            }
            if (!Board::InBounds(x, y)) {
                TraceLog(LOG_WARNING, "Piece '%s' out of bounds (%d, %d)", type.c_str(), x, y);
                continue;
            }
            board.AddPiece(it->second, x, y);
        }
    }
private:
    static inline std::unordered_map<std::string, PieceType> pieceNames = {
        {"Pawn", PieceType::Pawn},     {"Rook", PieceType::Rook},
        {"Bishop", PieceType::Bishop}, {"Knight", PieceType::Knight},
        {"Queen", PieceType::Queen},   {"King", PieceType::King},
    };
};


