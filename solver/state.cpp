//
// Created by admin on 21.05.2023.
//

#include "state.h"
#include "map"
#include "string"
#include "iostream"
#include "algorithm"
#include "position.h"

State::State(Position player, const std::vector<Position> &boxes, const std::vector<std::vector<bool>>& boxes_matrix) : player(player), boxes(boxes), boxes_matrix(boxes_matrix) {}

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


//int main() {
//
//    std::vector<Position> boxes = { {1, 1}, {3, 1}, {5, 6} };
//    std::vector<Position> goals = { {5, 6}, {1, 1}, {3, 1} };
//    Position p{1,2};
//    State solver(p, boxes);
////    int result = solver.distance(goals);
////    std::cout << "Результат: " << result << std::endl;
//    std::cout << solver.success(goals);
//
//    return 0;
//}