#include "k_s_server.h"
#include "k_s_client.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    char* newArgv[argc -1];
    newArgv[0] = argv[0];
    for(int i = 2; i<= argc;i++) {
     newArgv[i-1] = argv[i];
    }

    if(strcmp(argv[1], "k_s_server") == 0) {
       return k_s_server(argc -1, newArgv);
    }
    else if(strcmp(argv[1], "k_s_client") == 0) {
        return k_s_client(argc -1, newArgv);
    }
    else {
            fprintf(stderr,"Sever je nutne spustit s arguememtami\n");
            return 1;
        }
}