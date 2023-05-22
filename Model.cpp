//
// Created by Nikita on 22.05.2023.
//

#include "Model.h"
#include <fstream>
#include <iostream>

std::vector<std::vector<char>> Model::level_from_file() {
    std::vector<std::vector<char>> res;
    std::string line;
    std::ifstream in("C:\\Users\\Nikita\\Desktop\\sokoban\\sokoban_game\\levels\\level");
    while (std::getline(in, line)) {
        std::vector<char> tmp;
        for (char & i : line) {
            tmp.push_back(i);
        }
        res.push_back(tmp);
    }
    return res;
}
