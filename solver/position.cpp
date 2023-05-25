//
// Created by admin on 22.05.2023.
//

#include "position.h"

Position::Position(int i, int j) : row(i), col(j) { }

bool Position::operator<(const Position &rhs) const {
    if (row == rhs.row) {
        return col < rhs.col;
    }
    return row < rhs.row;
}

bool Position::operator==(const Position &rhs) const {
    return (row == rhs.row) && (col == rhs.col);
}

bool Position::operator!=(const Position &rhs) const {
    return (row != rhs.row) || (col != rhs.col);
}
