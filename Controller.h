//
// Created by Nikita on 21.05.2023.
//

#pragma once


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

    void setPuzzle(const std::vector<std::vector<char>> &level);

    bool isSolved();

public:
    Puzzle puzzle_;
    Model model_;
    bool solved_ = false;
};

