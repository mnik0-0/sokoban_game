//
// Created by Nikita on 25.05.2023.
//

#ifndef GAME_SOKOBAN_STATE_SOLVER_H
#define GAME_SOKOBAN_STATE_SOLVER_H

#include "position.h"
#include <vector>
#include <functional>

class StateS {
public:
    StateS(Position player, const std::vector<std::vector<bool>> &boxes_matrix);

    bool operator<(const StateS &rhs) const;

    bool operator==(const StateS &rhs) const;

public:
    Position player;
    std::vector<std::vector<bool>> boxes_matrix;
};

#endif //GAME_SOKOBAN_STATE_SOLVER_H
