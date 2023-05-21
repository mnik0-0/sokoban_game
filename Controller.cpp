//
// Created by Nikita on 21.05.2023.
//

#include "Controller.h"
#include "solver/move.h"

Controller::Controller() {
    get_start_puzzle();
}

void Controller::get_start_puzzle() {
    Puzzle puzzle;
    puzzle.walls = {{0, 1, 0, 1, 0, 0},
             {0, 1, 0, 1, 1, 1},
             {1, 1, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 1},
             {1, 1, 1, 0, 1, 0},
             {0, 0, 1, 0, 1, 0}};
    puzzle.player = {3, 3};
    puzzle.boxes = {{2, 2}, {2, 4}, {3, 2}, {4, 3}};
    puzzle.goals = {{0, 2}, {2, 5}, {3, 0}, {5, 3}};

    puzzle_ = puzzle;
}

void Controller::get_next_puzzle(char direction) {
    Move * mv = nullptr;
    switch (direction) {
        case 'u':
            mv = new Up(puzzle_.walls);
            break;
        case 'd':
            mv = new Down(puzzle_.walls);
            break;
        case 'l':
            mv = new Left(puzzle_.walls);
            break;
        case 'r':
            mv = new Right(puzzle_.walls);
            break;
    }

    State * state = mv->get_state(State(puzzle_.player, puzzle_.boxes));
    if (state == nullptr) {
        return;
    }

    puzzle_.boxes = state->boxes;
    puzzle_.player = state->player;

    delete state;
    delete mv;

}

std::vector<std::vector<char>> Controller::get_current_matrix() {
    return converterToString(puzzle_);
}

std::vector<std::vector<char>> Controller::converterToString(Puzzle puzzle) {
    std::vector<std::vector<char>> res(puzzle.walls.size(), std::vector<char>(puzzle.walls[0].size(), ' '));

    for (int i = 0; i < puzzle.walls.size(); ++i) {
        for (int j = 0; j < puzzle.walls[0].size(); ++j) {
            if (puzzle.walls[i][j]) {
                res[i][j] = '#';
            }
        }
    }

    for (const auto & it : puzzle.boxes) {
        if (res[it.row][it.col] == '#') {
            return {};
        }
        res[it.row][it.col] = '$';
    }

    for (const auto & it : puzzle.goals) {
        if (res[it.row][it.col] == '#') {
            return {};
        }
        if (res[it.row][it.col] == '$') {
            res[it.row][it.col] = '*';
            continue;
        }
        res[it.row][it.col] = '.';
    }

    if (res[puzzle.player.row][puzzle.player.col] == '#') {
        return {};
    }
    if (res[puzzle.player.row][puzzle.player.col] == '.') {
        res[puzzle.player.row][puzzle.player.col] = '+';
        return res;
    }
    res[puzzle.player.row][puzzle.player.col] = '@';

    return res;
}
