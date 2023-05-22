//
// Created by Nikita on 21.05.2023.
//

#include "Controller.h"
#include "solver/move.h"
#include "Model.h"

Controller::Controller() {
    model_ = Model();
    get_start_puzzle();
}

void Controller::get_start_puzzle() {
    std::vector<std::vector<char>> tmp = model_.level_from_file();

    puzzle_ = converterToPuzzle(tmp);

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

Puzzle Controller::converterToPuzzle(std::vector<std::vector<char>> data) {
    Puzzle puzzle;
    puzzle.walls = std::vector<std::vector<int>>(data.size(), std::vector<int>(data[0].size(), 0));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            switch (data[i][j]) {

                case '#': // стена - черный
                    puzzle.walls[i][j] = 1;
                    break;

                case '@': // игрок - красный
                    puzzle.player = Position{i, j};
                    break;

                case '+': // игрок + гоал - розоватый
                    puzzle.player = Position{i, j};
                    puzzle.goals.push_back(Position{i, j});
                    break;

                case '$': // бокс - коричневый
                    puzzle.boxes.push_back(Position{i, j});
                    break;

                case '*': // бокс + гоал - зеленый
                    puzzle.goals.push_back(Position{i, j});
                    puzzle.boxes.push_back(Position{i, j});
                    break;

                case '.': // гоал - зеленый
                    puzzle.goals.push_back(Position{i, j});
                    break;

                case ' ': // пустота - белый
                    break;

            }
        }
    }
    return puzzle;
}

std::string Controller::get_solution() {
    Solver solver(puzzle_);
    return solver.Solve();
}
