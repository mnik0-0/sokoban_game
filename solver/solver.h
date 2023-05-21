#include <iostream>
#include <vector>
#include <algorithm>
#include "state.h"
#include "move.h"


class Puzzle {
public:
    std::vector<std::vector<int>> walls;
    Position player;
    std::vector<Position> boxes;
    std::vector<Position> goals;

};

class Solver {
public:
    Solver(const Puzzle& puzzle) : puzzle_(puzzle) {}

    std::string Solve() {
        State initial_state(puzzle_.player, puzzle_.boxes);
        int bound = initial_state.distance(puzzle_.goals) * 2;
        std::vector<State> path {initial_state};

        while (true) {
            bool found;
            int value;
            std::tie(found, value) = Search(path, 0, bound);
            if (found) {
                std::string res;
                for (size_t state_index = 1; state_index < path.size(); ++state_index) {
                    if (path[state_index - 1].player.row < path[state_index].player.row) {
                        res += "Down ";
                    } else if (path[state_index - 1].player.row > path[state_index].player.row) {
                        res += "Up ";
                    } else if (path[state_index - 1].player.col < path[state_index].player.col) {
                        res += "Right ";
                    } else {
                        res += "Left ";
                    }
                }
                return res;
            }
            if (value == INT_MAX) {

                return "Not found";
            }
            bound = value;
        }
    }

private:
    std::tuple<bool, int> Search(std::vector<State>& path, int current_cost, int bound) {
        State node = path.back();
        int new_cost = current_cost + node.distance(puzzle_.goals);
        if (new_cost > bound) {
            return std::make_tuple(false, new_cost);
        }
        if (node.success(puzzle_.goals)) {

            return std::make_tuple(true, bound);
        }
        int minimum = INT_MAX;
        std::vector<Move*> moves { new Up(puzzle_.walls), new Down(puzzle_.walls), new Right(puzzle_.walls), new Left(puzzle_.walls) };

        for (Move* move : moves) {
            if (!move->can_move_in_direction(node)) {
                continue;
            }
            State* new_state = move->get_state(node);
            if (new_state == nullptr) {
                continue;
            }
            if (std::find(path.begin(), path.end(), *new_state) == path.end()) {
                path.push_back(*new_state);
                bool found;
                int value;
                search_calls_++;
                std::tie(found, value) = Search(path, current_cost + 1, bound);
                if (found) {
                    return std::make_tuple(true, bound);
                }
                if (value != -1 && (minimum == -1 || value < minimum)) {
                    minimum = value;
                }
                path.pop_back();
            }
        }
        return std::make_tuple(false, minimum);
    }

//    void PrintSolution(const std::vector<State>& path) {
//        std::cout << std::endl;
//        std::cout << "Solution:" << std::endl;
//        for (const State& state : path) {
//            std::cout << "Player: (" << state.player.row << ", " << state.player.col << ") ";
//            std::cout << "Boxes: ";
//            for (const Position& box : state.boxes) {
//                std::cout << "(" << box.row << ", " << box.col << ") ";
//            }
//            std::cout << std::endl;
//        }
//    }

private:
    Puzzle puzzle_;
    int search_calls_ = 0;
};

int main() {
    Puzzle puzzle;
    puzzle.walls = {
            {0, 1, 0, 1, 0, 0},
            {0, 1, 0, 1, 1, 1},
            {1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1},
            {1, 1, 1, 0, 1, 0},
            {0, 0, 1, 0, 1, 0}
    };
    puzzle.player = {3, 3};
    puzzle.boxes = {{2, 2}, {2, 4}, {3, 2}, {4, 3}};
    puzzle.goals = {{0, 2}, {2, 5}, {3, 0}, {5, 3}};

    Solver solver(puzzle);
    std::cout << solver.Solve();

    return 0;
}