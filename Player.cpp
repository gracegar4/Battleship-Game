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
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
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
    if (ship.get_size() > MAX_SHIP_SIZE) {
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
    int row = pos.get_row();
    int col = pos.get_col();
    char &target = opponent.grid[row][col];

    char col_letter = 'A' + col;
    int row_number = row + 1;

    if (target == HIT_LETTER || target == MISS_LETTER) {
        cout << endl << name << " (" << row_number << "," << col_letter << ") miss" << endl;
        return;
    }

    bool hit = false;
    for (int i = 0; i < opponent.num_ships; i++) {
        Ship &ship = opponent.ships[i];
        if (ship.has_position(pos)) {
            ship.hit();
            target = HIT_LETTER;
            guess_grid[row][col] = HIT_LETTER;
            hit = true;

            cout << endl << name << " (" << row_number << "," << col_letter << ") hit" << endl;

            if (ship.has_sunk()) {
                opponent.remaining_ships--;
                announce_ship_sunk(ship.get_size());
            }
            break;
        }
    }

    if (!hit) {
        target = MISS_LETTER;
        guess_grid[row][col] = MISS_LETTER;
        cout << name << " (" << row_number << "," << col_letter << ") miss" << endl;
    }
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
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    num_ships = 0;
    remaining_ships = 0;
    init_grid();

    string start_pos_str;
    string end_pos_str;
    while (file >> start_pos_str >> end_pos_str) {
        int start_row;
        int start_col;
        int end_row;
        int end_col;

        if (start_pos_str[0] == '(') {
            start_row = start_pos_str[1] - '1';
            start_col = toupper(start_pos_str[3]) - 'A';

            end_row = end_pos_str[1] - '1';
            end_col = toupper(end_pos_str[3]) - 'A';
        }
        else {
            start_row = start_pos_str[0] - '1';
            start_col = toupper(start_pos_str[1]) - 'A';

            end_row = end_pos_str[0] - '1';
            end_col = toupper(end_pos_str[1]) - 'A';
        }

        Position start(start_row, start_col);
        Position end(end_row, end_col);

        Ship ship(start, end);
        add_ship(ship);
    }

    file.close();
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

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
