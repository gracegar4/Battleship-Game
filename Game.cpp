/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Grace Garbaty
 * gracegar@umich.edu
 *
 * Project 4: Battleship
 *
 * Implementations for the class Game. This will be used to represent a game of battleship
 * Each game has two players, Player1 and Player2.
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    bool loadedGrid1 = false;
    bool loadedGrid2 = false;
    
    if (grid1 != "") {
        loadedGrid1 = p1.load_grid_file(grid1);
    }
    if (!loadedGrid1) {
        cout << "Generating random grid for " << p1.get_name();
    }
    if (grid2 != "") {
        loadedGrid2 = p2.load_grid_file(grid2);
    }
    if (!loadedGrid2) {
        cout << "Generating random grid for " << p2.get_name();
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    cout << player_name << " enter your move :";
    string move;
    cin >> move;
    return move;
}

bool Game::check_valid_move(string move) {
    if (move.length() != 2) {
        //Move length must be 2 characters long
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    char row_val = move[0];
    char col_val = toupper(move[1]);
    if (row_val < '1' || row_val > '8' || col_val < 'A' || col_val > 'H') {
        //Checking for valid input between grid (1-8) and (A-H)
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    return true;
}

void Game::start(char difficulty, int max_num_rounds) {
    // TODO: write implementation here.
    string winner_name = "";
    if (max_num_rounds == MAX_ROUNDS) {
        cout << "Game over, winner is " << winner_name << " in " << endl;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

