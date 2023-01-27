#include "policko.h"

POLICKO *Policko() {
    POLICKO *Policko = malloc(sizeof(POLICKO));
    //if (Policko == NULL)
      //  return NULL;
    return Policko;
}

void Policko_free(POLICKO *Policko) {
    free(Policko);
}