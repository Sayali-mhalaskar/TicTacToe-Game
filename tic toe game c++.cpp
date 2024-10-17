#include <iostream>
#include <cstdlib>   // For system("clear")
#include <string>    // For std::string
#include <cctype>    // For toupper function
using namespace std;

// Global Variables
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char player1Marker, player2Marker;
int currentPlayer = 1; // Player 1 always starts
bool hasWinner = false;

// Function to clear the console
void clearScreen() {
#if defined(_WIN32)
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and Mac
#endif
}

// Function to center text output
void centerText(string text, int padding) {
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << text << endl;
}

// Function to draw the game board
void drawBoard() {
    clearScreen(); // Clear the screen before drawing the board
    centerText("     |     |     ", 0);
    centerText("  " + string(1, board[0][0]) + "  |  " + string(1, board[0][1]) + "  |  " + string(1, board[0][2]), 0);
    centerText("_____|_____|_____", 0);
    centerText("     |     |     ", 0);
    centerText("  " + string(1, board[1][0]) + "  |  " + string(1, board[1][1]) + "  |  " + string(1, board[1][2]), 0);
    centerText("_____|_____|_____", 0);
    centerText("     |     |     ", 0);
    centerText("  " + string(1, board[2][0]) + "  |  " + string(1, board[2][1]) + "  |  " + string(1, board[2][2]), 0);
    centerText("     |     |     ", 0);
}

// Function to place a marker on the board
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = (currentPlayer == 1) ? player1Marker : player2Marker;
        return true;
    }
    return false;
}

// Function to check for a winner
bool checkWinner() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

// Function to swap players
void swapPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

// Function to choose markers
void chooseMarker() {
    char marker;
    centerText("Player 1, choose your marker (X or O): ", 20);
    cin >> marker;

    // Convert the marker to uppercase for consistency
    marker = toupper(marker);

    // Accept only valid markers
    while (marker != 'X' && marker != 'O') {
        centerText("Please choose 'X' or 'O': ", 20);
        cin >> marker;
        marker = toupper(marker); // Convert again to uppercase
    }

    player1Marker = marker;
    player2Marker = (player1Marker == 'X') ? 'O' : 'X';

    centerText("Player 1 is '" + string(1, player1Marker) + "' and Player 2 is '" + string(1, player2Marker) + "'.", 20);
    cin.ignore();
    cin.get(); // Wait for the user to press Enter before starting the game
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

// Main game function
void playGame() {
    clearScreen();
    chooseMarker(); // Ask player to choose markers
    hasWinner = false; // Reset the winner status at the beginning
    int round = 0;

    while (round < 9) { // Maximum rounds is 9 (3x3 board)
        clearScreen();
        drawBoard();

        cout << "Player " << currentPlayer << "'s turn. Enter your slot: ";
        int slot;
        cin >> slot;

        if (placeMarker(slot)) {
            round++;
            if (checkWinner()) {
                hasWinner = true;
                break; // Exit the loop if there's a winner
            }
            swapPlayer();
        }
        else {
            cout << "Invalid move. Try again.\n";
            cin.ignore();
            cin.get();
        }
    }

    clearScreen();
    drawBoard();

    // Check if there's a winner and display the appropriate message
    if (hasWinner) {
        centerText("Congratulations Player " + to_string(currentPlayer) + ", you won!\n", 20);
    }
    else {
        centerText("It's a draw!\n", 20);
    }
}

// Main function
int main() {
    playGame();
    return 0;
}
