#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QTcpSocket>
#include <QHostAddress>

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define BOARD_SIZE 100
#define BOARD_ROWS 20
#define BOARD_COLS 5

QTcpSocket socket;
char board[BOARD_ROWS][BOARD_COLS];
int playerPositions[NUM_PLAYERS][NUM_PIECES];
bool gameOver = false;

void initBoard() {
    // Initialize all squares to empty space
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            board[i][j] = ' ';
        }
    }

    // Set up the special squares
    board[0][2] = 'S'; // "Start" square
    board[19][2] = 'F'; // "Finish" square

    // Set up the "safe" squares
    for (int i = 0; i < BOARD_ROWS; i += 5) {
        for (int j = 0; j < BOARD_COLS; j += 2) {
            board[i][j] = 'O'; // "Safe" square
        }
    }
}

void printBoard() {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void movePiece(int player, int piece, int spaces) {
    // Update the position of the piece on the board
    playerPositions[player][piece] += spaces;
    int row = playerPositions[player][piece] / BOARD_COLS;
    int col = playerPositions[player][piece] % BOARD_COLS;

    // Update the board to reflect the new position of the piece
    board[row][col] = 'A' + player;
}

// Send a move to the server
void sendMove(int player, int piece, int spaces) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << "MOVE" << player << piece << spaces;
    socket.write(data);
}

// Process a move message received from the server
void processMove(QDataStream& stream) {
    int player, piece, spaces;
    stream >> player >> piece >> spaces;
    movePiece(player, piece, spaces);
}

// Process an error message received from the server
void processError(QDataStream& stream) {
    QString errorMessage;
    stream >> errorMessage;
    printf("Error: %s\n", errorMessage.toStdString().c_str());
}

// Process a win message received from the server
void processWin(QDataStream& stream) {
    int player;
    stream >> player;
    printf("Player %d wins!\n", player);
    gameOver = true;
}

// Process incoming data from the server
void processData() {
    QDataStream stream(socket);
    while (socket.bytesAvailable()) {
        QString messageType;
        stream >> messageType;
        if (messageType == "MOVE") {
            processMove(stream);
        }
        else if (messageType == "ERROR") {
            processError(stream);
        }
        else if (messageType == "WIN") {
            processWin(stream);
        }
    }
}

int main(int argc, char* argv[]) {
    // Seed the random number generator
    srand(time(NULL));

    // Initialize the board
    initBoard();

    // Initialize the player positions
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            playerPositions[i][j] = -1;
        }
    }

    // Connect to the server
    socket.connectToHost(QHostAddress("127.0.0.1"), 1234);

    // Main game loop
    while (!gameOver) {
        // Check for incoming data from the server
        processData();

        if (socket.state() == QTcpSocket::ConnectedState) {
            // Roll the dice and move the piece
            int roll = rand() % 6 + 1;
            printf("Player %d rolled a %d\n", player + 1, roll);

            // Choose which piece to move
            int piece = 0; // TODO: Choose which piece to move based on player strategy
            sendMove(player, piece, roll);
        }

        // Print the board
        printBoard();
    }

    // Close the socket when the game is over
    socket.close();

    return 0;
}

