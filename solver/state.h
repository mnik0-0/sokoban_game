//
// Created by admin on 21.05.2023.
//

#ifndef GAME_SOKOBAN_STATE_H
#define GAME_SOKOBAN_STATE_H

#include <vector>
#include <string>

struct Position {
    int row;
    int col;
};

bool operator==(const Position &a, const Position &b);

class State {
public:
    State(Position player, const std::vector<Position> &boxes);

    bool success(const std::vector<Position>& goals);

    static int manh_distance(const Position &box, const Position &goal);

    int distance(const std::vector<Position>& goals);

public:
    Position player;
    std::vector<Position> boxes;
};

bool operator==(const State& a, const State& b);

#endif //GAME_SOKOBAN_STATE_H
