/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Grace Garbaty
 * gracegar@umich.edu
 *
 * Project 4: Battleship
 *
 * Implementations of class Player. Used to keep track of each player's ships.
 * Ships to keep track of are Destroyer, Submarine, Battleship, and Carrier.
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; i ++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    if (row >= 0 && row < MAX_GRID_SIZE && col >= 0 && col < MAX_GRID_SIZE) {
        return grid[row][col];
    }
    return '?';
}

char Player::get_guess_grid_at(int row, int col) {
    if (row >= 0 && row < MAX_GRID_SIZE && col >= 0 && col < MAX_GRID_SIZE) {
        return guess_grid[row][col];
    }
    return '?';
}

void Player::add_ship(Ship ship) {
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    }
    
    for (int k = 0; k < num_ships; k++) {
        Ship &existing = ships[k];
        for (int i = 0; i < MAX_GRID_SIZE; i++) {
            for (int j = 0; j < MAX_GRID_SIZE; j++) {
                Position pos(i, j);
                if (ship.has_position(pos) && existing.has_position(pos)) {
                    return;
                }
            }
        }
    }
    Position start = ship.get_start();
    Position end = ship.get_end();
    int start_row = start.get_row();
    int start_col = start.get_col();
    int end_row = end.get_row();
    int end_col = end.get_col();
    if (ship.is_horizontal()) {
        if (start_col <= end_col) {
            for (int i = start_col; i <= end_col; i++) {
                grid[start_row][i] = SHIP_LETTER;
            }
        }
        else {
            for (int i = end_col; i <= start_col; i++) {
                grid[start_row][i] = SHIP_LETTER;
            }
        }
    }
    else {
        if (start_row <= end_row) {
            for (int j = start_row; j <= end_row; j++) {
                grid[j][start_col] = SHIP_LETTER;
            }
        }
        else {
            for (int j = end_row; j <= start_row; j++) {
                grid[j][start_col] = SHIP_LETTER;
            }
        }
    }
    ships[num_ships] = ship;
    num_ships++;
    remaining_ships++;
}

void Player::attack(Player &opponent, Position pos) {
    char mark = opponent.grid[pos.get_row()][pos.get_col()];
    if (mark == HIT_LETTER || mark == MISS_LETTER) {
        cout << name << " (" << pos.get_row() << "," << pos.get_col() << ") miss" << endl;
        return;
    }
    for (Ship &ship : opponent.ships) {
        if (ship.has_position(pos)) {
            ship.hit();
            remaining_ships--;
            cout << name << " (" << pos.get_row() << "," << pos.get_col() << ") hit" << endl;
            grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
            guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
            if (ship.has_sunk()) {
                opponent.announce_ship_sunk(ship.get_size());
            }
            return;
        }
    }
    cout << name << " (" << pos.get_row() << "," << pos.get_col() << ") miss" << endl;
    grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
    guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
}

void Player::announce_ship_sunk(int size) {
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer" << endl;
    }
    else if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine" << endl;
    }
    else if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship" << endl;
    }
    else if (size == 5) {
        cout << "Congratulations " << name << "! You sunk a Carrier" << endl;
    }
}

bool Player::load_grid_file(string filename) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Could not open file " << filename << endl;
//        return false;
//    }
//    string line;
//    num_ships = 0;
//    remaining_ships = 0;
//    istringstream inSS(line);
//    while (getline(file, line)) {
//        int start;
//        int end;
//        char ship_space;
//        inSS.clear();
//        inSS.str(line);
       // inSS >> start;
       // inSS >> end;
        //Ship ship(Position(start), Position(end));
        //ship.add_ship();
//        for (int row = 0; row < MAX_GRID_SIZE; row++) {
//            for (int col = 0; col < MAX_GRID_SIZE; col++) {
//                if (file >> ship_space) {
//                    grid[row][col] = SHIP_LETTER;
//                }
//                else {
//                    return false;
//                }
//            }
//        }
        //Position start(start_row, start_col);
        //Position end(end_row, end_col);
        //Ship ship(start, end);
        //add_ship(ship);
//    }
//    file.close();
    return true;
}

bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    else {
        return false;
    }
}

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
