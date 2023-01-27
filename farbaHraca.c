#include "farbaHraca.h"

FARBA_HRACA *FarbaHraca_new() {
    FARBA_HRACA *farba = malloc(sizeof(FARBA_HRACA));
    if (farba == NULL) {
    return NULL;
    printf("Hra sa nevytvorila.\n");
    }
    printf("Hra sa vytvorila.\n");
    return farba;
}
void Farba_free(FARBA_HRACA *farba) {
    free(farba);
}