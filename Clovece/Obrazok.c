#include "Obrazok.h"
OBRAZOK *obrazok(char obr) {
    OBRAZOK *obrazok = malloc(sizeof(OBRAZOK));
    obrazok->o = &obr;
}