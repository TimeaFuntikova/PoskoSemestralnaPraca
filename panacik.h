//
// Created by timka on 23. 1. 2023.
//

#ifndef POSKOSEMESTRALNAPRACA_PANACIK_H
#define POSKOSEMESTRALNAPRACA_PANACIK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "farbaHraca.h"
#include "stavPanacika.h"
#include "Obrazok.h"

extern const int MAX_PREJDENYCH;

typedef struct panacik {
    int idPanacikaPanacik;
    int idHracaPanacik;
    int poziciaX;
    int poziciaY;
    int pocetPrejdenychPolicok;
    FARBA_HRACA farbaHraca;
    STAV_PANACIKA stavPanacika;
    OBRAZOK obrazok;
} PANACIK;
PANACIK *Panacik_new(int idPanacika_, int idHraca_, FARBA_HRACA farbaHraca_);
void Panacik_free(PANACIK *panacik);

int getIdHraca(PANACIK *panacik);
int getPocetPrejdenychPolicok(PANACIK *p);
int getIdPanacika(PANACIK *p);
int getPoziciaX(PANACIK *p);
int getPoziciaY(PANACIK *p);
bool jeNaKonci(PANACIK *p);
bool jePredCielom(PANACIK *p, int pocetNaKocke);
bool pripocitajPrejdenePolicka(PANACIK *p, int pocetNaKocke);
void nastavPoziciu(PANACIK *p, int pX_, int pY_);
void nastavPanacikaNaPoziciu(PANACIK *p, int pX_, int pY_);
void nastavPanacikaNaDomovskuPoziciu(PANACIK *p, int pX_, int pY_);
void nastavPanacikaNaNovuPoziciu(PANACIK *p, int pX_, int pY_);
void nastavPanacikaNaStartovaciuPoziciu(PANACIK *p, int pX_, int pY_);
void nastavPanacikaNaCielovuPoziciu(PANACIK *p, int pX_, int pY_);
void posunPanacikaPanacik(PANACIK *p, int posunVodorovne, int posunZvislo);
void nastavObrazok(PANACIK *panacik);
void zmazPanacika(PANACIK *p);
void vypisStavPanacik(PANACIK *p);

#endif //POSKOSEMESTRALNAPRACA_PANACIK_H
