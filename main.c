#include "k_s_server.h"
#include "k_s_client.h"
//#include <string.h>
#include <stdio.h>
#include <time.h>
#include "hraClovece.h"

int main(int argc, char* argv[]) {
    HRA_CLOVECE *clovece = hra();
    novaHra(clovece);
    Hra_free(clovece);
    printf("Koniec Programu.\n");
    /*
    srand(time(NULL));

    //./posko server 10050
    if(strcmp(argv[1], "server") == 0) {
        return server(argc, argv);
    }
        //./posko client localhost 10050
    else if(strcmp(argv[1], "client") == 0) {
        return client(argc, argv);
    }
    else {
        fprintf(stderr,"Zle argumenty!\n");
        return 1;
    }
     */
}