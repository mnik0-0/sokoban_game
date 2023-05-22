#pragma once

#include "state.h"
#include "position.h"
#include "puzzle.h"
#include <map>
#include <queue>
class Solver {
public:
    enum class Path {
        right,
        left,
        down,
        up,
        none
    };

    std::map<State, bool> answer; // true, если из состояния State можно получить выигрышную позицию
    std::vector<Position> goals; // база
    std::vector<std::vector<bool>> wall; // база


    std::map<State, Path> next; // куда нужно из State перейти, чтобы приблизится к выигрышной позиции
    std::map<State, State> nextState;


    bool checkWall(int i, int j) {
        if (i < 0 || j < 0 || i >= wall.size() || j >= wall[i].size()) {
            return true;
        }
        return wall[i][j];
    }


    void getAns() {
        // добавляем в очередь все выигрышные State
        std::vector<int> per; // вспомогательынй массив
        for (int i = 0; i < goals.size(); ++i) {
            per.push_back(i);
        }

        std::queue<State> q;
        // перебираем все перестановки
        do {
            State vertex{{0, 0},
                         {{0, 0}}};
            // расставляем ящики по клеткам goals
            vertex.boxes.resize(goals.size(), {0, 0});
            for (int i = 0; i < goals.size(); ++i) {
                vertex.boxes[per[i]] = goals[i];
            }
            // расставляем главного героя
            for (int i = 0; i < wall.size(); ++i) {
                for (int j = 0; j < wall[i].size(); ++j) {
                    if (checkWall(i, j) || std::find(goals.begin(), goals.end(), Position(i, j)) != goals.end()) {
                        continue;
                    }
                    vertex.player = {i, j};
                    answer[vertex] = true;
                    next[vertex] = Path::none;
                    q.push(vertex);
                }
            }
        } while (std::next_permutation(per.begin(), per.end()));
        // пока есть состояния, из которых можно получить новые
        while (!q.empty()) {
            const State vertex = q.front();
            q.pop();
//        std::cout <<
//                  vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                  << vertex.boxes[0].col << std::endl;
            // начинаем перебор всех State, из которых можно попасть в состояние vertex
            for (int sg1: {-1, 1}) {
                for (int sg2: {0}) {
                    const Position pos{vertex.player.row + sg1, vertex.player.col + sg2};
                    State st{pos, std::vector<Position>(vertex.boxes)};
                    if (checkWall(vertex.player.row + sg1, vertex.player.col + sg2) ||
                        std::find(vertex.boxes.begin(), vertex.boxes.end(), pos) != vertex.boxes.end()) {
                        continue;
                    }
                    // если не было еще такого состояния
//                std::cout << st.hero.row << " " << st.hero.col << " " << st.boxes[0].row << " " << st.boxes[0].col
//                          << "  in   " <<
//                          vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                          << vertex.boxes[0].col << " " << answer[st] << std::endl;
                    if (!answer[st]) {
//                    std::cout << st.hero.row << " " << st.hero.col << " " << st.boxes[0].row << " " << st.boxes[0].col
//                              << "  in   " <<
//                              vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                              << vertex.boxes[0].col << std::endl;
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
                    const auto it = std::find(st.boxes.begin(), st.boxes.end(), pos2);
                    if (it == st.boxes.end()) {
                        continue;
                    }
                    st.boxes[it - st.boxes.begin()] = vertex.player;
                    if (!answer[st]) {
//                    std::cout << st.hero.row << " " << st.hero.col << " " << st.boxes[0].row << " " << st.boxes[0].col
//                              << "  in   " <<
//                              vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                              << vertex.boxes[0].col << std::endl;
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
                    State st{pos, vertex.boxes};
                    if (checkWall(vertex.player.row + sg1, vertex.player.col + sg2) ||
                        std::find(vertex.boxes.begin(), vertex.boxes.end(), pos) != vertex.boxes.end()) {
                        continue;
                    }
                    // если не было еще такого состояния
                    if (!answer[st]) {
//                    std::cout << st.hero.row << " " << st.hero.col << " " << st.boxes[0].row << " " << st.boxes[0].col
//                              << "  in   " <<
//                              vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                              << vertex.boxes[0].col << std::endl;
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
                    const auto it = std::find(st.boxes.begin(), st.boxes.end(), pos2);
                    if (it == st.boxes.end()) {
                        continue;
                    }
                    st.boxes[it - st.boxes.begin()] = vertex.player;
                    if (!answer[st]) {
//                    std::cout << st.hero.row << " " << st.hero.col << " " << st.boxes[0].row << " " << st.boxes[0].col
//                              << "  in   " <<
//                              vertex.hero.row << " " << vertex.hero.col << " " << vertex.boxes[0].row << " "
//                              << vertex.boxes[0].col << std::endl;
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

    std::string get_string_solution(Puzzle puzzle) {
        wall = puzzle.walls;
        goals = puzzle.goals;
        getAns();
        Position startMan = puzzle.player;
        std::vector<Position> boxes = puzzle.boxes;
        State st{startMan, boxes};
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
