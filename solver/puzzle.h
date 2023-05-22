//
// Created by admin on 22.05.2023.
//

#pragma once

#include "position.h"
#include <vector>

class Puzzle {
public:
    std::vector<std::vector<bool>> walls;
    Position player;
    std::vector<Position> boxes;
    std::vector<Position> goals;

};

