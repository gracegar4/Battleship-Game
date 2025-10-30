/**
 * Copyright 2025 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;

void test_position();
void test_ship();
void test_player();
void test_game();
void test_project_setup();

void startTests() {
    test_project_setup();
    test_position();
    test_ship();
    test_player();
    
    return;
}

void test_position() {
    // testing Position default constructor here
    Position start_pos;
    Position end_pos(12, 5);
    cout << "\nTesting Position: default and non-default\n";
    cout << "Position: (" << start_pos.get_row() << "," <<
        start_pos.get_col() <<  ")" << endl;
    // testing Positions non-default constructor here
    Position x2(-10, 10);
    cout << "Position: (" << x2.get_row() << "," << x2.get_col() << ")"
        << endl;
        
    Position x3('2', 'B');
    cout << "Position: (" << x3.get_row() << "," << x3.get_col() << ")"
        << endl;
    cout << "Position: (" << end_pos.get_row() << "," <<
        end_pos.get_col() << ")" << endl;
    Position x4('2', 'b');
    cout << "Position: (" << x4.get_row() << "," << x4.get_col() << ")"
        << endl;
    // testing Position setters here
    start_pos.set_row(1);
    start_pos.set_col(4);
    cout << "\nTesting Position::set_row() and Position::set_col()\n";
    cout << "start_pos, expected output: (2,E) actual output: " << start_pos
        << endl;
        
    // testing Position read
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {

        // can use the Position::read() function directly
        start_pos.read(input_file);
        // or use the extraction operator
        input_file >> end_pos;
        cout << "\nTesting Position::read()\n";
        cout << "start_pos, expected output: (8,B) actual output: " << start_pos
            << endl;
        cout << "end_pos, expected output: (8,C) actual output: " << end_pos << endl;
    }
    else {
        cout << "\nError opening grid1.txt\n";
    }
    return;
}

void test_ship() {
    cout << "\nTesting Ship: default and non-default\n";
    Ship s1;
    cout << "Default ship size: " << s1.get_size() << endl;
    Position p1(2, 3);
    Position p2(2, 6);
    Position p3(2, 7);
    Position p4(2, 2);
    Position p5(2, 5);
    Ship s2(p1, p2);
    cout << "Non-Default ship size: " << s2.get_size() << endl;
    cout << "\nTesting Ship: Horizontal ship\n";
    cout << "Ship should be horizontal: " << s2.is_horizontal() << endl;
    
    cout << "\nTesting Ship: Has_Position\n";
    Ship s10(Position(2, 5), Position(5, 5));
    Ship s11(Position(4, 5), Position(4, 2));
    cout << s10.has_position(Position(2, 5)) << ": Should be 1!" << endl;
    cout << s10.has_position(Position(5, 5)) << ": Should be 1!" << endl;
    cout << s10.has_position(Position(3, 5)) << ": Should be 1!" << endl;
    cout << s11.has_position(Position(3, 3)) << ": Should be 0!" << endl;
    cout << s11.has_position(Position(5, 5)) << ": Should be 0!" << endl;
    cout << s11.has_position(Position(4, 6)) << ": Should be 0!" << endl;
    cout << s11.has_position(Position(4, 3)) << ": Should be 1!" << endl;
    
    
    cout << "\nTesting Ship: Hits\n";
    Ship s3(Position(2, 3), Position(2, 6));
    s3.hit();
    cout << s3.has_sunk() << ": Should be 0!" << endl;
    s3.hit();
    cout << s3.has_sunk() << ": Should be 0!" << endl;
    s3.hit();
    s3.hit();
    cout << s3.has_sunk() << ": Should be 1!" << endl;
    Ship s4(Position(2, 3), Position(5, 3));
    s4.hit();
    cout << s4.has_sunk() << ": Should be 0!" << endl;
    s4.hit();
    s4.hit();
    s4.hit();
    cout << s4.has_sunk() << ": Should be 1!" << endl;
    s4.hit();
    cout << s4.has_sunk() << ": Should be 1!" << endl;
    return;
}

void test_player() {
    cout << "\nTesting Player: add_ship, overlap, and constructors\n";
    Ship s30(Position(0, 7), Position(0, 4));
    Ship s31(Position(1, 5), Position(2, 5));
    Ship s32(Position(1, 5), Position(3, 5));
    Player p1("Johnny");
    Player p2("Sam");
    cout << "Names should be 'Johnny and Sam' Actual: " << p1.get_name() <<
        " " << p2.get_name() << endl;
    cout << "Initial ships should be 0 Actual: " << p1.get_num_ships() << endl;
    p1.add_ship(s30);
    cout << "Total should be 1, Actual: " << p1.get_num_ships() << endl;
    p1.add_ship(s31);
    cout << "Total should be 2, Actual: " << p1.get_num_ships() << endl;
    p1.add_ship(s32);
    cout << "Overlap occuring, should be 2, Actual: " << p1.get_num_ships() << endl;
    p1.print_grid();
    Ship s33(Position(1, 7), Position(1, 4));
    Ship s34(Position(1, 3), Position(1, 5));
    Ship s35(Position(2, 2), Position(2, 4));
    Ship s36(Position(3, 0), Position(4, 0));
    Ship s37(Position(0, 0), Position(0, 2));
    Ship s38(Position(7, 7), Position(7, 5));
    Ship s39(Position(5, 3), Position(5, 4));
    p2.add_ship(s33);
    cout << "Total should be 1, Actual: " << p2.get_num_ships() << endl;
    p2.add_ship(s34);
    cout << "Overlap occuring, should be 1, Actual: " << p2.get_num_ships() << endl;
    p2.add_ship(s35);
    p2.add_ship(s36);
    p2.add_ship(s37);
    p2.add_ship(s38);
    p2.add_ship(s39);
    p2.print_grid();
    cout << "\nTesting Player: Hit or miss\n";
    p2.attack(p2, Position(3, 0));
    cout << "Should be a hit" << endl;
    p2.attack(p2, Position(3, 0));
    cout << "Should be a miss" << endl;
    p2.attack(p2, Position(4, 0));
    cout << "Should be a hit and sunk" << endl;
    p2.attack(p2, Position(0, 7));
    cout << "Should be a miss" << endl;
    p2.print_grid();
    p2.load_grid_file("grid1.txt");
    Player p3;
    Ship s40;
    cout << "should all be default: " << p3.get_name() << " " << p3.get_num_ships()
        << " " << p3.get_remaining_ships() << endl;
    p3.print_grid();
    p3.load_grid_file("grid1.txt");
    p3.load_grid_file("grid.txt");
    p3.print_grid();
    return;
}

void test_project_setup() {
    ifstream ins;
    ins.open("grid1.txt");

    if (ins.fail()) {
        cout << "Project was not created correctly." << endl;
        cout << "Text files are not in the correct folder." << endl;
        cout << "Check the project specification "
            << "for how to set up your project." << endl;
    }
    else {
        cout << "Project set up correctly, file opened." << endl;
    }

    return;
}
