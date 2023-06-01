//
// Created by Nikita on 22.05.2023.
//

#pragma once

#include <vector>

class Model {
public:
    std::vector<std::vector<char>> levelFromFile(int idLevel = -1);
    int getMaxId();

    void saveLevel(const std::vector<std::vector<char>> &vector);
};

