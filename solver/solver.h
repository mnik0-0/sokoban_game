#pragma once

#include "state_solver.h"
#include "position.h"
#include "puzzle.h"
#include <map>
#include <queue>
#include <algorithm>
#include <QDebug>
#include <functional>
#include <utility>



struct PositionHash {
    std::size_t operator()(const Position& pos) const {
        std::size_t hash = 0;
        std::hash<int> int_hasher;

        hash = int_hasher(pos.col);
        hash ^= int_hasher(pos.row) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }
};


struct BoolMatrixHash {
    std::size_t operator()(const std::vector<std::vector<bool>>& matrix) const {
        std::size_t hash = 0;
        std::hash<bool> bool_hasher;

        for (const auto& row : matrix) {
            for (const auto& element : row) {
                hash^= bool_hasher(element) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
        }

        return hash;
    }
};

struct StateSHash {
    std::size_t operator()(const StateS& state)const {
        std::size_t hash = 0;
        std::hash<Position> position_hasher(PositionHash);
        std::hash<std::vector<std::vector<bool>>> matrix_hasher(BoolMatrixHash);

        PositionHash positionHash;
        BoolMatrixHash boolMatrixHash;
        hash = positionHash(state.player);
        hash ^= boolMatrixHash(state.boxes_matrix) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }
};


class Solver {
public:
    enum class Path {
        right,
        left,
        down,
        up,
        none
    };

    // std::map<StateS, bool> answer; // true, если из состояния State можно получить выигрышную позицию
    std::vector<Position> goals; // база
    std::vector<std::vector<bool>> wall; // база


//    std::unordered_map<StateS, bool, StateSHash> answer;
    std::unordered_map<StateS, Path, StateSHash> next;

//    std::map<StateS, Path> next; // куда нужно из State перейти, чтобы приблизится к выигрышной позиции

    // std::map<StateS, StateS> nextState;


    bool checkWall(int i, int j) {
        if (i < 0 || j < 0 || i >= wall.size() || j >= wall[i].size()) {
            return true;
        }
        return wall[i][j];
    }


    void getAns(Position player, const std::vector<std::vector<bool>>& boxes) {
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

        StateS vertex{{0, 0},
                     {{0, 0}}};
        // расставляем ящики по клеткам goals


        vertex.boxes_matrix = goals_matrix;

        std::map<Position, int> positions;
        // расставляем главного героя
        for (int i = 0; i < wall.size(); ++i) {
            for (int j = 0; j < wall[i].size(); ++j) {
                if (checkWall(i, j) || !goals_matrix[i][j]) {
                    continue;
                }
                if (!goals_matrix[i + 1][j] && goals_matrix[i][j]) {
                    vertex.player = {i + 1, j};
//                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                    }
                    if (vertex.boxes_matrix == boxes && vertex.player == player) {
                        return;
                    }
                }
                if (!goals_matrix[i - 1][j] && goals_matrix[i][j]) {
                    vertex.player = {i - 1, j};
//                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                    }
                    if (vertex.boxes_matrix == boxes && vertex.player == player) {
                        return;
                    }
                }
                if (!goals_matrix[i][j + 1] && goals_matrix[i][j]) {
                    vertex.player = {i, j + 1};
//                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                    }
                    if (vertex.boxes_matrix == boxes && vertex.player == player) {
                        return;
                    }
                }

                if (!goals_matrix[i][j - 1] && goals_matrix[i][j]) {
                    vertex.player = {i, j - 1};
//                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                    }
                    if (vertex.boxes_matrix == boxes && vertex.player == player) {
                        return;
                    }
                }
            }
        }


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

                    if (next.count(st) <= 0) {

                        q.push(st);
//                        answer[st] = true;
                        // nextState.insert({st, vertex});
                        // запоминаем, куда нужно идти из состояния State
                        if (sg1 == -1) {
                            next[st] = Path::down;
                        } else {
                            next[st] = Path::up;
                        }
                        if (st.boxes_matrix == boxes && st.player == player) {
                            return;
                        }
                    }
                    // пробуем сделать движение ящика назад (например #iz <- iz#)
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};

                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;
                    if (next.count(st) <= 0) {

                        q.push(st);
//                        answer[st] = true;
                        // nextState.insert({st, vertex});
                        if (sg1 == -1) {
                            next[st] = Path::down;
                        } else {
                            next[st] = Path::up;
                        }
                        if (st.boxes_matrix == boxes && st.player == player) {
                            return;
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
                    if (next.count(st) <= 0) {

                        q.push(st);
//                         answer[st] = true;
                        // nextState.insert({st, vertex});
                        // запоминаем, куда нужно идти из состояния State
                        if (sg2 == -1) {
                            next[st] = Path::right;
                        } else {
                            next[st] = Path::left;
                        }
                        if (st.boxes_matrix == boxes && st.player == player) {
                            return;
                        }
                    }
                    // пробуем сделать движение ящика назад (например #iz <- iz#)
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};


                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;
                    if (next.count(st) <= 0) {

                        q.push(st);
//                        answer[st] = true;
                        // nextState.insert({st, vertex});
                        if (sg2 == -1) {
                            next[st] = Path::right;
                        } else {
                            next[st] = Path::left;
                        }
                        if (st.boxes_matrix == boxes && st.player == player) {
                            return;
                        }
                    }
                }
            }
        }
    }

    std::string get_string_solution(const Puzzle& puzzle) {
        wall = puzzle.walls;
        goals = puzzle.goals;

        Position startMan = puzzle.player;

        std::vector<std::vector<bool>> boxes_matrix(puzzle.walls.size(), std::vector<bool>(puzzle.walls[0].size(), 0));
        for (auto & it : puzzle.boxes) {
            boxes_matrix[it.row][it.col] = 1;
        }

        StateS st{startMan, boxes_matrix};
        Position last_player = startMan;

        getAns(startMan, boxes_matrix);

        std::string res;
        while (next.count(st) > 0) {
            switch (next[st]) {
                case Path::right:
                    st.player.col++;
                    if (st.boxes_matrix[st.player.row][st.player.col]) {
                        st.boxes_matrix[st.player.row][st.player.col] = 0;
                        st.boxes_matrix[st.player.row][st.player.col + 1] = 1;
                    }
                    res += "r ";
                    break;
                case Path::left:
                    st.player.col--;
                    if (st.boxes_matrix[st.player.row][st.player.col]) {
                        st.boxes_matrix[st.player.row][st.player.col] = 0;
                        st.boxes_matrix[st.player.row][st.player.col - 1] = 1;
                    }
                    res += "l ";
                    break;
                case Path::down:
                    st.player.row++;
                    if (st.boxes_matrix[st.player.row][st.player.col]) {
                        st.boxes_matrix[st.player.row][st.player.col] = 0;
                        st.boxes_matrix[st.player.row + 1][st.player.col] = 1;
                    }
                    res += "d ";
                    break;
                case Path::up:
                    st.player.row--;
                    if (st.boxes_matrix[st.player.row][st.player.col]) {
                        st.boxes_matrix[st.player.row][st.player.col] = 0;
                        st.boxes_matrix[st.player.row - 1][st.player.col] = 1;
                    }
                    res += "u ";
                    break;
                case Path::none:
                    return res;
            }
            // st = nextState.at(st);
        }
        return res;
    }


};
