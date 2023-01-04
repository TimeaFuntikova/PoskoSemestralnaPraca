#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//
#include <string.h>
#include <unistd.h>
int client(int argc, char const *argv[])
/*{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("%d\n", (AF_INET, argv[1], &serv_addr.sin_addr) );
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    // Connecting to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    // User commands
    int valread;
    char buffer[1024] = {0};
    char command[50];
    while (1)
    {
        printf("> ");
        gets(command);
        send(sock, command, strlen(command), 0);
        if (strcmp(command, "stop") == 0)
        {
            printf("Disconnected\n");
            break;
        }
        valread = read(sock, buffer, sizeof(buffer));
        if (valread < 0)
        {
            perror("Reading failed");
            exit(EXIT_FAILURE);
        }

        printf("< %s\n", buffer);
        printf("%s\n", buffer);
    }

    return 0;
}
*/


#include "k_s_definitions.h"
#include "k_s_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int client(int argc, char *argv[]) {
    if (argc < 3) {
        printError("Klienta je nutne spustit s nasledujucimi argumentmi: adresa port.");
    }
    // The hostname and port are provided as command line arguments
    const char *hostname = argv[1];
    const char *port = argv[2];

    // Set up hints for the getaddrinfo function
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // use IPv4
    hints.ai_socktype = SOCK_STREAM; // use TCP

    // Get address info for the server
    struct addrinfo *serverAddress;
    int gai_result = getaddrinfo(hostname, port, &hints, &serverAddress);
    if (gai_result != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(gai_result));
        exit(EXIT_FAILURE);
    }

    // Create the socket
    int sock = socket(serverAddress->ai_family, serverAddress->ai_socktype, serverAddress->ai_protocol);
    if (sock < 0) {
        printError("Chyba - socket.");
    }

    // Connect to the server
    if (connect(sock, serverAddress->ai_addr, serverAddress->ai_addrlen) < 0) {
        printError("Chyba - connect.");
    }

    // Free the address info
    freeaddrinfo(serverAddress);

    printf("Spojenie so serverom bolo nadviazane.\n");
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    int koniec = 0;
    while (!koniec) {
        fgets(buffer, BUFFER_LENGTH, stdin);
        char* pos = strchr(buffer, '\n');
        if (pos != NULL) {
            *pos = '\0';
        }
        // Write data to the socket <unistd.h>
        write(sock, buffer, strlen(buffer) + 1);
        if (strcmp(buffer, endMsg) != 0) {
            // Read data from the socket <unistd.h>
            read(sock, buffer, BUFFER_LENGTH);
            printf("Server poslal nasledujuce data:\n%s\n", buffer);
        }
        else {
            koniec = 1;
        }
    }
    // Close the socket <unistd.h>
    close(sock);
    printf("Spojenie so serverom bolo ukoncene.\n");

    return (EXIT_SUCCESS);
}
