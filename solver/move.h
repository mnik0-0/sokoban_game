//
// Created by admin on 21.05.2023.
//
#pragma once

#include "vector"
#include "state.h"

class Move {
public:
    Move(const std::vector<std::vector<bool>> &walls);

    State *getState(const State &state);

    virtual bool canMoveInDirection(const State& state) const = 0;

    virtual bool canMoveBoxInDirection(const State& state) const = 0;

    virtual int nextRow(const State& state) const = 0;

    virtual int nextCol(const State& state) const = 0;

    virtual int nextNextRow(const State& state) const = 0;

    virtual int nextNextCol(const State& state) const = 0;


public:
    std::vector<std::vector<bool>> walls;
};

class Up : public Move {
public:
    Up(const std::vector<std::vector<bool>>& walls) : Move(walls) {}

    bool canMoveInDirection(const State& state) const override {
        return state.player.row > 0;
    }

    bool canMoveBoxInDirection(const State& state) const override {
        return state.player.row > 1;
    }

    int nextRow(const State& state) const override {
        return state.player.row - 1;
    }

    int nextCol(const State& state) const override {
        return state.player.col;
    }

    int nextNextRow(const State& state) const override {
        return state.player.row - 2;
    }

    int nextNextCol(const State& state) const override {
        return state.player.col;
    }
};

class Down : public Move {
public:
    Down(const std::vector<std::vector<bool>>& walls) : Move(walls) {}

    bool canMoveInDirection(const State& state) const override {
        return state.player.row < walls.size() - 1;
    }

    bool canMoveBoxInDirection(const State& state) const override {
        return state.player.row < walls.size() - 2;
    }

    int nextRow(const State& state) const override {
        return state.player.row + 1;
    }

    int nextCol(const State& state) const override {
        return state.player.col;
    }

    int nextNextRow(const State& state) const override {
        return state.player.row + 2;
    }

    int nextNextCol(const State& state) const override {
        return state.player.col;
    }
};

class Left : public Move {
public:
    Left(const std::vector<std::vector<bool>>& walls) : Move(walls) {}

    bool canMoveInDirection(const State& state) const override {
        return state.player.col > 0;
    }

    bool canMoveBoxInDirection(const State& state) const override {
        return state.player.col > 1;
    }

    int nextRow(const State& state) const override {
        return state.player.row;
    }

    int nextCol(const State& state) const override {
        return state.player.col - 1;
    }

    int nextNextRow(const State& state) const override {
        return state.player.row;
    }

    int nextNextCol(const State& state) const override {
        return state.player.col - 2;
    }
};

class Right : public Move {
public:
    Right(const std::vector<std::vector<bool>>& walls) : Move(walls) {}

    bool canMoveInDirection(const State& state) const override {
        return state.player.col < walls[0].size() - 1;
    }

    bool canMoveBoxInDirection(const State& state) const override {
        return state.player.col < walls[0].size() - 2;
    }

    int nextRow(const State& state) const override {
        return state.player.row;
    }

    int nextCol(const State& state) const override {
        return state.player.col + 1;
    }

    int nextNextRow(const State& state) const override {
        return state.player.row;
    }

    int nextNextCol(const State& state) const override {
        return state.player.col + 2;
    }
};

