//
// Created by Nikita on 21.05.2023.
//

#ifndef GAME_SOKOBAN_CONTROLLER_H
#define GAME_SOKOBAN_CONTROLLER_H

#include <vector>
#include <Qt>
#include <string>
#include "solver/state.h"
#include "solver/solver.h"

class Controller {
public:
    Controller();

    std::vector<std::vector<char>> converterToString(Puzzle puzzle);
    Puzzle converterToPuzzle();

    void get_start_puzzle();

    void get_next_puzzle(char direction);

    std::vector<std::vector<char>> get_current_matrix();

private:
    Puzzle puzzle_;
};

#endif //GAME_SOKOBAN_CONTROLLER_H
