#include "k_s_definitions.h"
#include "k_s_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

char* spracujData(char *data) {
    char *akt = data;
    while (*akt != '\0') {
        if (islower(*akt)) {
            *akt = toupper(*akt);
        }
        else if (isupper(*akt)) {
            *akt = tolower(*akt);
        }
        akt++;
    }
    return data;
}

int k_s_server(int argc, char** argv) {
    if (argc < 2) {
        printError("Sever je nutne spustit s nasledujucimi argumentmi: port.");
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        printError("Port musi byt cele cislo vacsie ako 0.");
    }

    //vytvorenie TCP socketu <sys/socket.h>
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printError("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         //internetove sockety
    serverAddress.sin_addr.s_addr = INADDR_ANY; //prijimame spojenia z celeho internetu
    serverAddress.sin_port = htons(port);       //nastavenie portu

    //prepojenie adresy servera so socketom <sys/socket.h>
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        printError("Chyba - bind.");
    }

    //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
    listen(serverSocket, 10);

    //server caka na pripojenie klienta <sys/socket.h>
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    //uzavretie pasivneho socketu <unistd.h>
    close(serverSocket);
    if (clientSocket < 0) {
        printError("Chyba - accept.");
    }

    printf("Klient sa pripojil na server.\n");
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    int koniec = 0;
    while (!koniec) {
        //citanie dat zo socketu <unistd.h>
        read(clientSocket, buffer, BUFFER_LENGTH);
        if (strcmp(buffer, endMsg) != 0) {
            printf("Klient poslal nasledujuce data:\n%s\n", buffer);
            spracujData(buffer);
            //zapis dat do socketu <unistd.h>
            write(clientSocket, buffer, strlen(buffer) + 1);
        }
        else {
            koniec = 1;
        }
    }
    printf("Klient ukoncil komunikaciu.\n");

    //uzavretie socketu klienta <unistd.h>
    close(clientSocket);

    return (EXIT_SUCCESS);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NUM_PLAYERS 2
#define NUM_TOKENS 4
#define BOARD_SIZE 20
#define MAX_MESSAGE_LEN 256

// Struct for a player
typedef struct {
    int tokens[NUM_TOKENS];
    int numTokensAtHome;
    int numTokensFinished;
    int sockfd;
} Player;

// Roll a 6-sided dice
int rollDice() {
    return rand() % 6 + 1;
}

// Initialize the players
void initPlayers(Player players[NUM_PLAYERS]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].numTokensAtHome = NUM_TOKENS;
        players[i].numTokensFinished = 0;
        for (int j = 0; j < NUM_TOKENS; j++) {
            players[i].tokens[j] = -1;
        }
    }
}

// Print the current state of the game
void printGameState(Player players[NUM_PLAYERS]) {
    printf("Current game state:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: %d tokens at home, %d tokens finished\n", i+1, players[i].numTokensAtHome, players[i].numTokensFinished);
        for (int j = 0; j < NUM_TOKENS; j++) {
            printf("  Token %d: ", j+1);
            if (players[i].tokens[j] == -1) {
                printf("At home\n");
            } else {
                printf("On square %d\n", players[i].tokens[j]);
            }
        }
    }
}

int main(int argc, char argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server/client> <port>\n", argv[0]);
        exit(1);
    }

    srand(time(0));

    charmode = argv[1];
    int port = atoi(argv[2]);
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    Player players[NUM_PLAYERS];
    initPlayers(players);

    if (strcmp(mode, "server") == 0) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }
        memset
        */