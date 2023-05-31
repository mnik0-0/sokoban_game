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

const long long MOD = 10000000000037;
const long long P = 23;

class Solver {
public:
    enum class Path {
        none,
        final,
        right,
        left,
        down,
        up,
    };
    std::vector<long long> step;
    long long get_hash(const StateS& stateS) {
        long long res = 0;

        res += stateS.player.col * step[0];
        res += (stateS.player.row * step[1]) % MOD;
        int p = 2;
        for (int i = 0; i < stateS.boxes_matrix.size(); ++i) {
            for (int j = 0; j < stateS.boxes_matrix[0].size(); ++j) {
                res = (res + (stateS.boxes_matrix[i][j] * step[p]) % MOD) % MOD;
                p++;
            }
        }

        return res;
    }

    long long get_next_hash(const StateS& stateS, long long old_hash, int x, int y, int row1, int col1, int row2, int col2) {


        old_hash = (old_hash - (stateS.player.col * step[0]) % MOD + MOD) % MOD;
        old_hash = (old_hash - (stateS.player.row * step[1]) % MOD + MOD) % MOD;

        old_hash = (old_hash + (x * step[0]) % MOD) % MOD;
        old_hash = (old_hash + (y * step[1]) % MOD) % MOD;

        if (row1 == -1) {
            return old_hash;
        }
        int row_size = stateS.boxes_matrix[0].size();

        bool item1 = stateS.boxes_matrix[row1][col1];
        bool item2 = stateS.boxes_matrix[row2][col2];

        old_hash = (old_hash - (item1 * step[row1 * row_size + col1 + 2]) % MOD + MOD) % MOD;
        old_hash = (old_hash - (item2 * step[row2 * row_size + col2 + 2]) % MOD + MOD) % MOD;

        std::swap(item1, item2);

        old_hash = (old_hash + (item1 * step[row1 * row_size + col1 + 2]) % MOD) % MOD;
        old_hash = (old_hash + (item2 * step[row2 * row_size + col2 + 2]) % MOD) % MOD;

        return old_hash;
    }

    std::vector<Position> goals; // база
    std::vector<std::vector<bool>> wall; // база

    std::unordered_map<long long, Path> next_ll;


    bool checkWall(int i, int j) {
        if (i < 0 || j < 0 || i >= wall.size() || j >= wall[i].size()) {
            return true;
        }
        return wall[i][j];
    }


    void getAns(Position player, const std::vector<std::vector<bool>>& boxes) {


        long long tmp = 1;
        for (int i = 0; i < 1000; ++i) {
            step.push_back(tmp);
            tmp = (tmp * P) % MOD;
        }

        StateS result_state = {player, boxes};
        long long result_hash = get_hash(result_state);

        std::vector<std::vector<bool>> goals_matrix(wall.size(), std::vector<bool>(wall[0].size(), 0));
        for (const Position &it: goals) {
            goals_matrix[it.row][it.col] = 1;
        }

        std::queue<StateS> q;
        std::queue<long long> q_hash;

        StateS vertex{{0, 0},
                     {{0, 0}}};


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
                    long long hash = get_hash(vertex);
                    next_ll[hash] = Path::final;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                        q_hash.push(hash);
                    }

                }
                if (!goals_matrix[i - 1][j] && goals_matrix[i][j]) {
                    vertex.player = {i - 1, j};
                    long long hash = get_hash(vertex);
                    next_ll[hash] = Path::final;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                        q_hash.push(hash);
                    }

                }
                if (!goals_matrix[i][j + 1] && goals_matrix[i][j]) {
                    vertex.player = {i, j + 1};
                    long long hash = get_hash(vertex);
                    next_ll[hash] = Path::final;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                        q_hash.push(hash);
                    }

                }

                if (!goals_matrix[i][j - 1] && goals_matrix[i][j]) {
                    vertex.player = {i, j - 1};
                    long long hash = get_hash(vertex);
                    next_ll[hash] = Path::final;
                    if (!checkWall(vertex.player.row, vertex.player.col) && positions.count(vertex.player) <= 0) {
                        positions.insert({vertex.player, 1});
                        q.push(vertex);
                        q_hash.push(hash);
                    }

                }
            }
        }


        while (!q.empty()) {
            const StateS vertex = q.front();
            long long old_hash = q_hash.front();
            q.pop();
            q_hash.pop();

            if (old_hash == result_hash) {
                return;
            }

            for (int sg1: {-1, 1}) {
                for (int sg2: {0}) {
                    const Position pos{vertex.player.row + sg1, vertex.player.col + sg2};
                    StateS st{pos, vertex.boxes_matrix};
                    if (checkWall(vertex.player.row + sg1, vertex.player.col + sg2) ||
                        vertex.boxes_matrix[pos.row][pos.col]) {
                        continue;
                    }
                    long long n_hash = get_next_hash(vertex, old_hash, st.player.col, st.player.row, -1, -1, -1, -1);
                    if (next_ll[n_hash] == Path::none) {
                        q.push(st);
                        q_hash.push(n_hash);
                        if (sg1 == -1) {
                            next_ll[n_hash] = Path::down;
                        } else {
                            next_ll[n_hash] = Path::up;
                        }

                    }
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};

                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;

                    long long n_hash_box = get_next_hash(vertex, old_hash, st.player.col, st.player.row, pos2.row, pos2.col, vertex.player.row, vertex.player.col);
                    if (next_ll[n_hash_box] == Path::none) {

                        q.push(st);
                        q_hash.push(n_hash_box);
                        if (sg1 == -1) {
                            next_ll[n_hash_box] = Path::down;
                        } else {
                            next_ll[n_hash_box] = Path::up;
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
                    long long n_hash = get_next_hash(vertex, old_hash, st.player.col, st.player.row, -1, -1, -1, -1);
                    if (next_ll[n_hash] == Path::none) {

                        q.push(st);
                        q_hash.push(n_hash);
                        if (sg2 == -1) {
                            next_ll[n_hash] = Path::right;
                        } else {
                            next_ll[n_hash] = Path::left;
                        }

                    }
                    Position pos2{vertex.player.row - sg1, vertex.player.col - sg2};


                    if (checkWall(pos2.row, pos2.col) || !st.boxes_matrix[pos2.row][pos2.col]) {
                        continue;
                    }
                    st.boxes_matrix[pos2.row][pos2.col] = 0;
                    st.boxes_matrix[vertex.player.row][vertex.player.col] = 1;
                    long long n_hash_box = get_next_hash(vertex, old_hash, st.player.col, st.player.row, pos2.row, pos2.col, vertex.player.row, vertex.player.col);
                    if (next_ll[n_hash_box] == Path::none) {

                        q.push(st);
                        q_hash.push(n_hash_box);
                        if (sg2 == -1) {
                            next_ll[n_hash_box] = Path::right;
                        } else {
                            next_ll[n_hash_box] = Path::left;
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


        getAns(startMan, boxes_matrix);

        std::string res;
        long long hash = get_hash(st);

        while (next_ll[hash] != Path::final) {
            switch (next_ll[hash]) {
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
                case Path::final:
                    return res;
            }
            hash = get_hash(st);
        }
        return res;
    }


};
