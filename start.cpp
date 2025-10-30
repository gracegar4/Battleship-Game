/**
 * Copyright 2025 University of Michigan EECS183
 *
 * start.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Grace Garbaty
 * gracegar@umich.edu
 *
 * Project 4: Battleship
 *
 * Start of the battleship game. User has the option of 1 or 2 to either test classes
 * or play the battleship game.
 */

#include <iostream>
#include <string>

using namespace std;

//********************************************************
// Function declarations. 
// Function definitions are in battleship.cpp and test.cpp
//********************************************************
void battleship();
void startTests();

int main() {
    
    cout << "-------------------------------" << endl
         << "EECS 183 Project 4 Menu Options" << endl
         << "-------------------------------" << endl;
    cout << "1) Execute testing functions in test.cpp" << endl;
    cout << "2) Execute battleship() function to play game" << endl;    
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    // remove the return character from the cin stream buffer
    string junk;
    getline(cin, junk);

    if (choice == 1) {
        startTests();
    }
    else if (choice == 2) {
        battleship();
    }
    
    return 0;
}
