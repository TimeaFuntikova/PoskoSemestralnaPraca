#include "k_s_server.h"
#include "k_s_client.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    char* newArgv[2];
    newArgv[0] = argv[0];
    newArgv[1] = argv[2];

    if(strcmp(argv[1], "server") == 0) {
        return server(2, newArgv);
    }
    else if(strcmp(argv[1], "client") == 0) {
        return client(argc - 1, argv);
    }
    else {
        fprintf(stderr,"Zle argumenty!\n");
        return 1;
    }
}