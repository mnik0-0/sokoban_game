//
// Created by admin on 21.05.2023.
//

#include "state.h"
#include "map"
#include "string"
#include "iostream"
#include "algorithm"
#include "position.h"

State::State(Position player, const std::vector<Position> &boxes) : player(player), boxes(boxes) {}

bool State::success(const std::vector<Position>& goals) {
    std::map<std::string, int> count;

    for (const Position & pos : boxes) {
        std::string tmp = std::to_string(pos.row) + " " + std::to_string(pos.col);

        count[tmp] += 1;
    }

    for (const Position & pos : goals) {
        std::string tmp = std::to_string(pos.row) + " " + std::to_string(pos.col);

        count[tmp] += 1;
    }

    for (auto it = count.begin(); it != count.end(); ++it) {
        if (it->second != 2) {
            return false;
        }
    }

    return true;
}

bool State::operator<(const State &rhs) const {
    if (player == rhs.player) {
        return boxes < rhs.boxes;
    }
    return player < rhs.player;
}

bool operator==(const State& a, const State& b) {
    return a.player == b.player && a.boxes == b.boxes;
}
