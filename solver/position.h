//
// Created by admin on 22.05.2023.
//
#pragma once

struct Position {
    char row;
    char col;

    Position() = default;

    Position(int i, int j);

    bool operator<(const Position &rhs) const;

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;

};
