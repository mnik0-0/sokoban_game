#pragma once

#include "state_solver.h"
#include "position.h"
#include "puzzle.h"
#include <map>
#include <queue>
#include <algorithm>
#include <QDebug>

class Solver {
public:
    enum class Path {
        right,
        left,
        down,
        up,
        none
    };

    std::map<StateS, bool> answer; // true, если из состояния State можно получить выигрышную позицию
    std::vector<Position> goals; // база
    std::vector<std::vector<bool>> wall; // база


    std::map<StateS, Path> next; // куда нужно из State перейти, чтобы приблизится к выигрышной позиции

    std::map<StateS, StateS> nextState;


    bool checkWall(int i, int j) {
        if (i < 0 || j < 0 || i >= wall.size() || j >= wall[i].size()) {
            return true;
        }
        return wall[i][j];
    }


    void getAns() {
        // пересчет goals в матрицу для быстрой работы
        std::vector<std::vector<bool>> goals_matrix(wall.size(), std::vector<bool>(wall[0].size(), 0));
        for (const Position &it: goals) {
            goals_matrix[it.row][it.col] = 1;
        }

        // добавляем в очередь все выигрышные State
        std::vector<int> per; // вспомогательынй массив
        for (int i = 0; i < goals.size(); ++i) {
            per.push_back(i);
        }

        std::queue<StateS> q;
        // перебираем все перестановки
        do {
            StateS vertex{{0, 0},
                         {{0, 0}}};
            // расставляем ящики по клеткам goals


            vertex.boxes_matrix = goals_matrix;

            // расставляем главного героя
            for (int i = 0; i < wall.size(); ++i) {
                for (int j = 0; j < wall[i].size(); ++j) {
                    if (checkWall(i, j) || goals_matrix[i][j]) {
                        continue;
                    }
                    vertex.player = {i, j};
                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    q.push(vertex);
                }
            }
        } while (false);
        // пока есть состояния, из которых можно получить новые
        while (!q.empty()) {
            const StateS vertex = q.front();
            q.pop();

            // начинаем перебор всех State, из которых можно попасть в состояние vertex
            for (int sg1: {-1, 1}) {
                for (int sg2: {0}) {
                    const Position pos{vertex.player.row + sg1, vertex.player.col + sg2};
                    StateS st{pos, vertex.boxes_matrix};
                    if (checkWall(vertex.player.row + sg1, vertex.player.col + sg2) ||
                        vertex.boxes_matrix[pos.row][pos.col]) {
                        continue;
                    }
                    // если не было еще такого состояния

                    if (!answer[st]) {

                        q.push(st);
                        answer[st] = true;
                        nextState.insert({st, vertex});
                        // запоминаем, куда нужно идти из состояния State
                        if (sg1 == -1) {
                            next[st] = Path::down;
                        } else {
                            next[st] = Path::up;
                        }
                    }
                    // пробуем сделать движение ящика назад (например #iz <- iz#)
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};

                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;
                    if (!answer[st]) {

                        q.push(st);
                        answer[st] = true;
                        nextState.insert({st, vertex});
                        if (sg1 == -1) {
                            next[st] = Path::down;
                        } else {
                            next[st] = Path::up;
                        }
                    }
                }
            }


            for (int sg1: {0}) {
                for (int sg2: {-1, 1}) {
                    Position pos{vertex.player.row + sg1, vertex.player.col + sg2};
                    StateS st{pos, vertex.boxes_matrix};
                    if (checkWall(vertex.player.row + sg1, vertex.player.col + sg2) ||
                        vertex.boxes_matrix[pos.row][pos.col]) {
                        continue;
                    }
                    // если не было еще такого состояния
                    if (!answer[st]) {

                        q.push(st);
                         answer[st] = true;
                        nextState.insert({st, vertex});
                        // запоминаем, куда нужно идти из состояния State
                        if (sg2 == -1) {
                            next[st] = Path::right;
                        } else {
                            next[st] = Path::left;
                        }
                    }
                    // пробуем сделать движение ящика назад (например #iz <- iz#)
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};


                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;
                    if (!answer[st]) {

                        q.push(st);
                        answer[st] = true;
                        nextState.insert({st, vertex});
                        if (sg2 == -1) {
                            next[st] = Path::right;
                        } else {
                            next[st] = Path::left;
                        }
                    }
                }
            }
        }
    }

    std::string get_string_solution(const Puzzle& puzzle) {
        wall = puzzle.walls;
        goals = puzzle.goals;
        getAns();
        Position startMan = puzzle.player;
        std::vector<std::vector<bool>> boxes_matrix(puzzle.walls.size(), std::vector<bool>(puzzle.walls[0].size(), 0));

        for (auto & it : puzzle.boxes) {
            boxes_matrix[it.row][it.col] = 1;
        }

        StateS st{startMan, boxes_matrix};
        Position last_player = startMan;
        std::string res;
        while (answer[st]) {
            switch (next[st]) {
                case Path::right:
                    res += "r ";
                    break;
                case Path::left:
                    res += "l ";
                    break;
                case Path::down:
                    res += "d ";
                    break;
                case Path::up:
                    res += "u ";
                    break;
                case Path::none:
                    return res;
            }
            st = nextState.at(st);
        }
        return res;
    }


};
