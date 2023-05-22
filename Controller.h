//
// Created by Nikita on 21.05.2023.
//

#pragma once

#ifndef GAME_SOKOBAN_CONTROLLER_H
#define GAME_SOKOBAN_CONTROLLER_H

#include <vector>
#include <Qt>
#include <string>
#include "solver/state.h"
#include "solver/solver.h"
#include "Model.h"

class Controller {
public:
    Controller();

    std::vector<std::vector<char>> converterToString(Puzzle puzzle);

    Puzzle converterToPuzzle(std::vector<std::vector<char>> data);

    void get_start_puzzle();

    void get_next_puzzle(char direction);

    std::vector<std::vector<char>> get_current_matrix();

    std::string get_solution();

public:
    Puzzle puzzle_;
    Model model_;
};

#endif //GAME_SOKOBAN_CONTROLLER_H
