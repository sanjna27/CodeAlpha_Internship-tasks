#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to print the Sudoku board
void printBoard(int board[SIZE][SIZE]) {
    cout << "\nSolved Sudoku:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if number is valid in current row, column and 3x3 subgrid
bool isValid(int board[SIZE][SIZE], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Backtracking solver
bool solveSudoku(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == 0) { // empty cell
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board))
                            return true;

                        board[row][col] = 0; // backtrack
                    }
                }
                return false; // no valid number found
            }
        }
    }
    return true; // solved
}

// Optional: Function to take user input
void inputBoard(int board[SIZE][SIZE]) {
    cout << "Enter the Sudoku puzzle (0 for empty cells):\n";
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            cin >> board[i][j];
}

int main() {
    // You can replace this with user input using `inputBoard(board);`
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Uncomment below line to take user input
    // inputBoard(board);

    if (solveSudoku(board)) {
        printBoard(board);
    } else {
        cout << "No solution exists!\n";
    }

    return 0;
}
