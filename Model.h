//
// Created by Nikita on 22.05.2023.
//

#pragma once

#ifndef GAME_SOKOBAN_MODEL_H
#define GAME_SOKOBAN_MODEL_H

#include <vector>

class Model {
public:
    std::vector<std::vector<char>> level_from_file();
};

#endif //GAME_SOKOBAN_MODEL_H
