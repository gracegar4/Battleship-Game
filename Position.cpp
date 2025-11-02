/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Grace Garbaty
 * gracegar@umich.edu
 *
 * Project 4: Battleship
 *
 * Implementation for Position.cpp, which determines the players positions
 * and moves on the battleship board. Input can be a char or an integer.
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    if (isdigit(row_in)) {
        row = check_range((row_in - '0') - 1);
    }
    else {
        row = check_range(toupper(row_in) - 'A');
    }
    if (isdigit(col_in)) {
        col = check_range((col_in - '0') - 1);
    }
    else {
        col = check_range(toupper(col_in) - 'A');
    }
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::write(ostream &os) {
    char col_letter = col + 'A';
    os << "(" << (row + 1) << "," << col_letter << ")";
    return;
}

int Position::check_range(int val) {
    if (val >= MAX_GRID_SIZE) {
        return MAX_GRID_SIZE - 1;
    }
    if (val < 0) {
        return 0;
    }
    else {
        return val;
    }
}

void Position::read(istream& is) {
    char trash = 't';
    int row_in = 0;
    char col_in = 'c';
    // read format 1A
    is >> row_in >> col_in;

    // if stream failed, must read format (1,A)
    if (is.fail()) {
        is.clear();
        is >> trash >> row_in >> trash >> col_in >> trash;
    }
    
    row = check_range(row_in - 1);
    col = check_range(toupper(col_in) - 'A');
    return;
}

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

