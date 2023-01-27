


#ifndef POSKOSEMESTRALNAPRACA_FARBAHRACA_H
#define POSKOSEMESTRALNAPRACA_FARBAHRACA_H
#include <stdlib.h>
#include <stdio.h>
typedef enum farbaHraca {
    ZELENA,
    CERVENA,
    MODRA,
    ZLTA
} FARBA_HRACA;

FARBA_HRACA *FarbaHraca_new();
void Farba_free(FARBA_HRACA *farba);

#endif //POSKOSEMESTRALNAPRACA_FARBAHRACA_H
