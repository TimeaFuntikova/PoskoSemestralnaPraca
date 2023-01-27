
#ifndef POSKOSEMESTRALNAPRACA_HRACIAPLOCHA_H
#define POSKOSEMESTRALNAPRACA_HRACIAPLOCHA_H
#include "farbaHraca.h"
#include <stdio.h>

const int POCET_BLOKOV = 11;

typedef struct plocha {
    char plocha[11][11];
    FARBA_HRACA farbyHracichBlokov[];

}PLOCHA;

PLOCHA *plocha();
void Plocha_free(PLOCHA *plocha);
void nacitajHraciuPlochu(PLOCHA *plocha);
void nacitajFarbyBlokov(PLOCHA *plocha);
void nacitajPlochu(PLOCHA *plocha);
void nacitajDrahu(PLOCHA *plocha);
void nacitajBlokyHracom(PLOCHA *plocha);
void nacitajDomovskeBloky(PLOCHA *plocha, int idBloku, int idPozicie, FARBA_HRACA farba);
void nacitajStartovacieBloky(PLOCHA *plocha, int idBloku, FARBA_HRACA farba);
void nacitajCieloveBloky(PLOCHA *plocha, int idBloku, int idPozicie, FARBA_HRACA farba);
char dajFarbuPanacika(FARBA_HRACA farba);char dajFarbuPanacika(FARBA_HRACA farba);
char dajFarbuStartu(FARBA_HRACA farba);
char dajFarbuDomu(FARBA_HRACA farba);
static PLOCHA dajPlocha();

#endif //POSKOSEMESTRALNAPRACA_HRACIAPLOCHA_H
