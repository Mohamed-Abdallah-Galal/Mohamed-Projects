//Program Description: A 3x3 board is displayed. Player 1 takes odd numbers (1, 3, 5, 7, 9) and player 2 takes even numbers (0, 2, 4, 6, 8) Players take turns to place their numbers on the board. The first player to complete a line that adds up to 15 wins The line can have both odd and even numbers.
//Author : Mohamed Abdallah Galal Hefnawy
//ID : 20231144
//Version : 1.0
//Date of creating : 1 / 3 /2024











#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Global variable to keep track of turns
int turn = 0;

// Function to check if any player has won
bool checkWin(string board[3][3]) {
    // Check rows for a win
    for (int i = 0; i < 3; i++) {
        // Check if all elements in a row are valid integers
        if (isdigit(board[i][0][0]) && isdigit(board[i][1][0]) && isdigit(board[i][2][0])) {
            int rsum = stoi(board[i][0]) + stoi(board[i][1]) + stoi(board[i][2]);
            if (rsum == 15) { // Check if the sum of elements in the row equals 15
                return true;
            }
        }
    }

    // Check columns for a win
    for (int i = 0; i < 3; i++) {
        // Check if all elements in a column are valid integers
        if (isdigit(board[0][i][0]) && isdigit(board[1][i][0]) && isdigit(board[2][i][0])) {
            int csum = stoi(board[0][i]) + stoi(board[1][i]) + stoi(board[2][i]);
            if (csum == 15) { // Check if the sum of elements in the column equals 15
                return true;
            }
        }
    }

    // Check diagonal sums if all elements are valid integers
    if (isdigit(board[0][0][0]) && isdigit(board[1][1][0]) && isdigit(board[2][2][0])) {
        int diagsum = stoi(board[0][0]) + stoi(board[1][1]) + stoi(board[2][2]);
        if (diagsum == 15) { // Check if the sum of elements in the main diagonal equals 15
            return true;
        }
    }

    if (isdigit(board[0][2][0]) && isdigit(board[1][1][0]) && isdigit(board[2][0][0])) {
        int inverse_diag_sum = stoi(board[0][2]) + stoi(board[1][1]) + stoi(board[2][0]);
        if (inverse_diag_sum == 15) { // Check if the sum of elements in the inverse diagonal equals 15
            return true;
        }
    }

    return false;
}

// Function to print the tic-tac-toe board
void print_the_board(string board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------" << endl;
    }
}

// Function to handle player input
void input(string board[3][3], vector<string>& available_oddelement, vector<string>& available_evenelement, vector<string>& available_indices) {

    string number;

    if (turn % 2 == 0) { // Player 1's turn
        turn++;
        cout << "Player 1, please enter the index of the row: ";
        string row;
        cin >> row;
        cout << endl;
        auto it = find(available_indices.begin(), available_indices.end(), row);
        while (it == available_indices.end()) {
            cout << "Invalid input. Player 1, please enter a valid index for the row: ";
            cin >> row;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), row);
        }

        cout << "Player 1, please enter the index of the column: ";
        string column;
        cin >> column;
        cout << endl;
        it = find(available_indices.begin(), available_indices.end(), column);
        while (it == available_indices.end()) {
            cout << "Invalid input. Player 1, please enter a valid index for the column: ";
            cin >> column;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), column);
        }
        int row_index = stoi(row);
        int col_index = stoi(column);

        // Check if the chosen cell is already occupied
        while (!board[row_index][col_index].empty()) {
            cout << "The chosen cell is already occupied. Please choose another one." << endl;
            cout << "Player 1, please enter the index of the row: ";
            cin >> row;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), row);
            while (it == available_indices.end()) {
                cout << "Invalid input. Player 1, please enter a valid index for the row: ";
                cin >> row;
                cout << endl;
                it = find(available_indices.begin(), available_indices.end(), row);
            }

            cout << "Player 1, please enter the index of the column: ";
            cin >> column;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), column);
            while (it == available_indices.end()) {
                cout << "Invalid input. Player 1, please enter a valid index for the column: ";
                cin >> column;
                cout << endl;
                it = find(available_indices.begin(), available_indices.end(), column);
            }

            row_index = stoi(row);
            col_index = stoi(column);
        }
        cout << "Player 1, please enter an odd number between 0 and 9: ";
        cin >> number;
        cout << endl;
        it = find(available_oddelement.begin(), available_oddelement.end(), number);
        while (it == available_oddelement.end() || stoi(number) % 2 == 0 || number.size() > 1) {
            cout << "Invalid input. Player 1, please choose an odd number between 0 and 9: ";
            cin >> number;
            cout << endl;
            it = find(available_oddelement.begin(), available_oddelement.end(), number);
        }
        available_oddelement.erase(it);
        board[stoi(row)][stoi(column)] = number;

    }
    else { // Player 2's turn (even numbers)
        turn++;
        cout << "Player 2, please enter the index of the row: ";
        string row;
        cin >> row;
        cout << endl;
        auto it = find(available_indices.begin(), available_indices.end(), row);
        while (it == available_indices.end()) { // Validate row input
            cout << "Invalid input. Player 2, please enter a valid index for the row: ";
            cin >> row;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), row);
        }
        cout << "Player 2, please enter the index of the column: ";
        string column;
        cin >> column;
        cout << endl;
        it = find(available_indices.begin(), available_indices.end(), column);
        while (it == available_indices.end()) { // Validate column input
            cout << "Invalid input. Player 2, please enter a valid index for the column: ";
            cin >> column;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), column);
        }
        int row_index = stoi(row);
        int col_index = stoi(column);

        // Check if the chosen cell is already occupied
        while (!board[row_index][col_index].empty()) {
            cout << "The chosen cell is already occupied. Please choose another one." << endl;
            cout << "Player 2, please enter the index of the row: ";
            cin >> row;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), row);
            while (it == available_indices.end()) { // Validate row input
                cout << "Invalid input. Player 2, please enter a valid index for the row: ";
                cin >> row;
                cout << endl;
                it = find(available_indices.begin(), available_indices.end(), row);
            }
            cout << "Player 2, please enter the index of the column: ";
            cin >> column;
            cout << endl;
            it = find(available_indices.begin(), available_indices.end(), column);
            while (it == available_indices.end()) { // Validate column input
                cout << "Invalid input. Player 2, please enter a valid index for the column: ";
                cin >> column;
                cout << endl;
                it = find(available_indices.begin(), available_indices.end(), column);
            }

            row_index = stoi(row);
            col_index = stoi(column);
        }

        cout << "Player 2, please enter an even number between 0 and 9: ";
        cin >> number;
        cout << endl;
        it = find(available_evenelement.begin(), available_evenelement.end(), number);
        while (it == available_evenelement.end() || stoi(number) % 2 != 0 || number.size() > 1) { // Validate even number input
            cout << "Invalid input. Player 2, please enter a valid even number between 0 and 9: ";
            cin >> number;
            cout << endl;
            it = find(available_evenelement.begin(), available_evenelement.end(), number);
        }
        available_evenelement.erase(it);
        board[stoi(row)][stoi(column)] = number;
    }
}

// The main function
int main() {
    // Display game description
    cout << "********************************Welcome to tic tac toe game**************************************" << endl;
    cout << "Description: A 3x3 board is displayed. Player 1 takes odd numbers (1, 3, 5, 7, 9) and player 2 takes even numbers (0, 2, 4, 6, 8).\n"
        "Players take turns to place their numbers on the board. The first player to complete a line that adds up to 15 wins.\n"
        "The line can have both odd and even numbers." << endl;
    cout << "=================================================================================================" << endl;

    // Initialize available numbers and the board
    vector<string> available_oddelement{ "1", "3", "5", "7", "9" };
    vector<string> available_evenelement{ "0", "2", "4", "6", "8" };
    vector<string> available_indices{ "0", "1", "2" };
    string board[3][3];

    // Game loop
    while (true) {
        // Print the current state of the board
        print_the_board(board);

        // Player input
        input(board, available_oddelement, available_evenelement, available_indices);

        // Check for a win
        if (checkWin(board)) {
            if (turn % 2 == 0) { // If it's an even turn, player 1 wins
                print_the_board(board);
                cout << "Player 1 wins!" << endl;
                exit(0);
            }
            else { // If it's an odd turn, player 2 wins
                print_the_board(board);
                cout << "Player 2 wins!" << endl;
                exit(0);
            }
        }
        else if (available_evenelement.empty() && available_oddelement.empty()) { // Check for a draw
            print_the_board(board);
            cout << "The game is a draw." << endl;
            exit(0);
        }
    }
    return 0;
}