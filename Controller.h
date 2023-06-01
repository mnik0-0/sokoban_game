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
    Controller(int id = -1);

    std::vector<std::vector<char>> converterToString(Puzzle puzzle);

    Puzzle converterToPuzzle(std::vector<std::vector<char>> data);

    void getStartPuzzle(int id = -1);

    void getNextPuzzle(char direction);

    std::vector<std::vector<char>> getCurrentMatrix();

    std::string getSolution();

    QString checkValid(const std::vector<std::vector<char>>& matrix);

    void setPuzzle(const std::vector<std::vector<char>> &level);

    int getMaxId();

    bool isSolved();

    std::vector<std::vector<char>> getPuzzleById(int id);

public:
    Puzzle puzzle_;
    Model model_;

    void saveLevel(const std::vector<std::vector<char>>& vector);
};

