/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Grace Garbaty
 * gracegar@umich.edu
 *
 * Project 4: Battleship
 *
 * Implementation of class type ship. Class ship will be used to determine size,
 * hits, orientation, and if the ship has sunk.
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    start = Position(0, 0);
    end = Position(0, 0);
    num_hits = 0;
    size = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    size = get_size();
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    if (is_horizontal()) {
        return size = abs(start.get_col() - end.get_col()) + 1;
    }
    else if (!(is_horizontal()) && (start.get_col() == end.get_col())) {
        return size = abs(start.get_row() - end.get_row()) + 1;
    }
    else {
        return size = 0;
    }
}

bool Ship::is_horizontal() {
    if (start.get_row() == end.get_row()) {
        return true;
    }
    else {
        return false;
    }
}

bool Ship::has_position(Position pos) {
    if (is_horizontal()) {
        if (pos.get_row() != start.get_row()) {
            return false;
        }
        int start_col = start.get_col();
        int end_col = end.get_col();
        if ((pos.get_col() >= start_col && pos.get_col() <= end_col)
            || (pos.get_col() >= end_col && pos.get_col() <= start_col)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (pos.get_col() != start.get_col()) {
            return false;
        }
        int start_row = start.get_row();
        int end_row = end.get_row();
        if ((pos.get_row() >= start_row && pos.get_row() <= end_row)
            || (pos.get_row() >= end_row && pos.get_row() <= start_row)) {
            return true;
        }
        else {
            return false;
        }
    }
}

void Ship::hit() {
    if (num_hits < get_size()) {
        num_hits++;
    }
}

bool Ship::has_sunk() {
    if (num_hits == size) {
        return true;
    }
    else {
        return false;
    }
}
