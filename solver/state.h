//
// Created by admin on 21.05.2023.
//
#pragma once

#include <vector>
#include <string>
#include "position.h"

class State {
public:
    State(Position player, const std::vector<Position> &boxes);

    bool success(const std::vector<Position>& goals);

    bool operator<(const State &rhs) const;

public:
    Position player;
    std::vector<Position> boxes;
};

bool operator==(const State& a, const State& b);
