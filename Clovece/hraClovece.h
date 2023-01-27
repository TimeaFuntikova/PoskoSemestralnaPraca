
#ifndef POSKOSEMESTRALNAPRACA_HRACLOVECE_H
#define POSKOSEMESTRALNAPRACA_HRACLOVECE_H
#include "hraciaPlocha.h"
#include "hrac.h"
#include "kocka.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int MAX_POCET_HRACOV = 4;
typedef struct hra {
    KOCKA kocka;
    HRAC hraci[4];
    HRAC aktualnyHrac;
    int pocetHracov;
    bool hraPrebieha;
    PLOCHA plocha;

}HRA_CLOVECE;

void Hra_free(HRA_CLOVECE *hra);

void uvolniPamat(HRA_CLOVECE *hra);
void novaHra(HRA_CLOVECE *hra);
void zacniHru(HRA_CLOVECE *hra);
void nastavPocetHracov(HRA_CLOVECE *hra);
void nasledujuciHrac(HRA_CLOVECE *hra);
int dajIndexHraca(HRA_CLOVECE *hra, int idAktualnyHrac_);
void hodKocku(HRA_CLOVECE *hra);
void tahHraca(HRA_CLOVECE *hra, int hodeneCisloNaKocke);
#endif //POSKOSEMESTRALNAPRACA_HRACLOVECE_H
