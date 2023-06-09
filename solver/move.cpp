//
// Created by admin on 21.05.2023.
//

#include "move.h"
#include "state.h"
#include "algorithm"

Move::Move(const std::vector<std::vector<bool>> &walls) : walls(walls) {}

State *Move::getState(const State &state) {
    if (!canMoveInDirection(state)) {
        return nullptr;
    }

    Position target_player_pos = Position{nextRow(state), nextCol(state)};

    if (walls[target_player_pos.row][target_player_pos.col]) {
        return nullptr;
    }

    if (std::find(state.boxes.begin(), state.boxes.end(), target_player_pos) == state.boxes.end()) {
        return new State(target_player_pos, state.boxes);
    } else {
        Position target_box_pos = Position{nextNextRow(state), nextNextCol(state)};
        if (canMoveBoxInDirection(state) &&
            !walls[target_box_pos.row][target_box_pos.col] &&
            std::find(state.boxes.begin(), state.boxes.end(), target_box_pos) == state.boxes.end()) {


            std::vector<Position> boxes_copy = state.boxes;
            boxes_copy.erase(std::find(boxes_copy.begin(), boxes_copy.end(), target_player_pos));
            boxes_copy.push_back(target_box_pos);
            return new State(target_player_pos, boxes_copy);
        }
    }
    return nullptr;
}

