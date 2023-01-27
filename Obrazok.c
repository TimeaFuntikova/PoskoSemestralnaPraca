#include "Obrazok.h"

OBRAZOK *obrazok(char *obr) {
    OBRAZOK *obrazok = malloc(sizeof(OBRAZOK));
    obrazok->o = obr;
    return obrazok;
}

void OBRAZOK_free(OBRAZOK *o) {
    free(o);
}