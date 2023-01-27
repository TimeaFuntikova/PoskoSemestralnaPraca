

#ifndef POSKOSEMESTRALNAPRACA_HRAC_H
#define POSKOSEMESTRALNAPRACA_HRAC_H

#include <stdbool.h>
#include "farbaHraca.h"
#include "panacik.h"

extern const int POCET_PANACIKOV;

typedef struct Hrac {
    int idHraca;
    int POCET_PANACIKOV;
    FARBA_HRACA farbaHraca;
    PANACIK panaciky[4];
    int idAktualnyPanacik;
    bool maPanacikaNaDrahe;
    bool maVsetkyPanacikyVCieli;
    int pocetHodovKocky;
}HRAC;

HRAC *hrac(int id, FARBA_HRACA farba);
void Hrac_free(HRAC *hrac);

void nasledujuciPanacik(HRAC *hrac);
int dajIndexPanacika(HRAC *hrac, int idPanacika_);
PANACIK* dajAktualnehoPanacika(HRAC *hrac, int idPanacik_);
void posunPanacika(HRAC *hrac, PANACIK *p, int cisloHoduKocky_);
void nastavitPanacikaNaStart(HRAC *hrac, PANACIK *p);
void nastavitPanacikaDoCiela(HRAC *hrac, PANACIK *panacik);
PANACIK* zoberPanacika(HRAC *hrac);
void vyhoditPanacika(HRAC *hrac, PANACIK *panacik);
void nacitajPanacikovHraca(HRAC *hrac);
void zmazVsetkychPanacikov(HRAC *hrac);
void nastavDomovPanacika(HRAC *hrac,PANACIK *panacik);
void vypisStavHrac(HRAC *hrac);
void hodilKocku(HRAC *hrac);
void vynulujPocetHodovKocky(HRAC *hrac);

#endif //POSKOSEMESTRALNAPRACA_HRAC_H
