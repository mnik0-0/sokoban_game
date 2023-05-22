//
// Created by admin on 21.05.2023.
//
#pragma once
#ifndef GAME_SOKOBAN_MOVE_H
#define GAME_SOKOBAN_MOVE_H

#include "vector"
#include "state.h"

class Move {
public:
    Move(const std::vector<std::vector<int>> &walls);

    State *get_state(const State &state);

    virtual bool can_move_in_direction(const State& state) const = 0;

    virtual bool can_move_box_in_direction(const State& state) const = 0;

    virtual int next_row(const State& state) const = 0;

    virtual int next_col(const State& state) const = 0;

    virtual int next_next_row(const State& state) const = 0;

    virtual int next_next_col(const State& state) const = 0;


public:
    std::vector<std::vector<int>> walls;
};

class Up : public Move {
public:
    Up(const std::vector<std::vector<int>>& walls) : Move(walls) {}

    bool can_move_in_direction(const State& state) const override {
        return state.player.row > 0;
    }

    bool can_move_box_in_direction(const State& state) const override {
        return state.player.row > 1;
    }

    int next_row(const State& state) const override {
        return state.player.row - 1;
    }

    int next_col(const State& state) const override {
        return state.player.col;
    }

    int next_next_row(const State& state) const override {
        return state.player.row - 2;
    }

    int next_next_col(const State& state) const override {
        return state.player.col;
    }
};

class Down : public Move {
public:
    Down(const std::vector<std::vector<int>>& walls) : Move(walls) {}

    bool can_move_in_direction(const State& state) const override {
        return state.player.row < walls.size() - 1;
    }

    bool can_move_box_in_direction(const State& state) const override {
        return state.player.row < walls.size() - 2;
    }

    int next_row(const State& state) const override {
        return state.player.row + 1;
    }

    int next_col(const State& state) const override {
        return state.player.col;
    }

    int next_next_row(const State& state) const override {
        return state.player.row + 2;
    }

    int next_next_col(const State& state) const override {
        return state.player.col;
    }
};

class Left : public Move {
public:
    Left(const std::vector<std::vector<int>>& walls) : Move(walls) {}

    bool can_move_in_direction(const State& state) const override {
        return state.player.col > 0;
    }

    bool can_move_box_in_direction(const State& state) const override {
        return state.player.col > 1;
    }

    int next_row(const State& state) const override {
        return state.player.row;
    }

    int next_col(const State& state) const override {
        return state.player.col - 1;
    }

    int next_next_row(const State& state) const override {
        return state.player.row;
    }

    int next_next_col(const State& state) const override {
        return state.player.col - 2;
    }
};

class Right : public Move {
public:
    Right(const std::vector<std::vector<int>>& walls) : Move(walls) {}

    bool can_move_in_direction(const State& state) const override {
        return state.player.col < walls[0].size() - 1;
    }

    bool can_move_box_in_direction(const State& state) const override {
        return state.player.col < walls[0].size() - 2;
    }

    int next_row(const State& state) const override {
        return state.player.row;
    }

    int next_col(const State& state) const override {
        return state.player.col + 1;
    }

    int next_next_row(const State& state) const override {
        return state.player.row;
    }

    int next_next_col(const State& state) const override {
        return state.player.col + 2;
    }
};

#endif //GAME_SOKOBAN_MOVE_H
