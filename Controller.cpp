//
// Created by Nikita on 21.05.2023.
//

#include "Controller.h"
#include "solver/move.h"
#include "Model.h"
#include "solver/puzzle.h"

Controller::Controller(int id) {
    model_ = Model();
    getStartPuzzle(id);
}

void Controller::getStartPuzzle(int id) {
    std::vector<std::vector<char>> tmp = model_.levelFromFile(id);
    puzzle_ = converterToPuzzle(tmp);
}

void Controller::getNextPuzzle(char direction) {
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
    State * state = mv->getState(State(puzzle_.player, puzzle_.boxes));
    if (state == nullptr) {
        return;
    }

    puzzle_.boxes = state->boxes;
    puzzle_.player = state->player;

    delete state;
    delete mv;

}

std::vector<std::vector<char>> Controller::getCurrentMatrix() {
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
    puzzle.walls = std::vector<std::vector<bool>>(data.size(), std::vector<bool>(data[0].size(), 0));
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

std::string Controller::getSolution() {
    Solver solver;
    return solver.get_string_solution(puzzle_);
}

void Controller::setPuzzle(const std::vector<std::vector<char>> &level) {
    puzzle_ = converterToPuzzle(level);
}

bool Controller::isSolved() {
    State * st = new State(puzzle_.player, puzzle_.boxes);
    bool res = st->success(puzzle_.goals);
    delete st;
    return res;
}

int Controller::getMaxId() {
    return model_.getMaxId();
}

std::vector<std::vector<char>> Controller::getPuzzleById(int id) {
    return model_.levelFromFile(id);
}
