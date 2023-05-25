//
// Created by Nikita on 25.05.2023.
//

#include "state_solver.h"

bool StateS::operator<(const StateS &rhs) const {
    if (player == rhs.player) {
        return boxes_matrix < rhs.boxes_matrix;
    }
    return player < rhs.player;
}

StateS::StateS(Position player, const std::vector<std::vector<bool>> &boxes_matrix) : player(player), boxes_matrix(boxes_matrix) {}

bool StateS::operator==(const StateS &rhs) const {
    return (player == rhs.player && boxes_matrix == rhs.boxes_matrix);
}

