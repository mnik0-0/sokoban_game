//
// Created by admin on 21.05.2023.
//

#include "state.h"
#include "map"
#include "string"
#include "iostream"
#include "algorithm"

bool operator==(const Position& a, const Position& b) {
    return (a.col == b.col) && (a.row == b.row);
}

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

int State::manh_distance(const Position &box, const Position &goal) {
    return abs(box.row - goal.row) + abs(box.col - goal.col);
}

int State::distance(const std::vector<Position> &goals) {
    std::vector<Position> tmp_boxes = boxes;
    int result = 0;
    for (const auto& goal : goals) {

        Position b{0, 0};
        int d = INT_MAX;
        for (const auto& box : tmp_boxes) {
            int dist = manh_distance(box, goal);
            if (dist < d) {
                b = box;
                d = dist;
            }
        }
        result += d;
        tmp_boxes.erase(std::find(tmp_boxes.begin(), tmp_boxes.end(), b));
    }
    return  result;
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