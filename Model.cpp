//
// Created by Nikita on 22.05.2023.
//

#include "Model.h"
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>
#include <QString>
#include <QDebug>
#include <QFile>

std::vector<std::vector<char>> Model::level_from_file() {

    QFile file(":levels/level2");
    file.open(QIODevice::ReadOnly|QIODevice::Text);


    srand(time(nullptr));
    std::vector<std::vector<char>> res;
    std::string line;
    while (!file.atEnd()) {
        QString s = file.readLine();

        std::vector<char> tmp;
        line = s.toStdString();
        for (int i = 0; i < line.size() - 1; i++) {
            tmp.push_back(line[i]);
        }

        res.push_back(tmp);
    }
    return res;
}
