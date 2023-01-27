
#ifndef POSKOSEMESTRALNAPRACA_KOCKA_H
#define POSKOSEMESTRALNAPRACA_KOCKA_H
#include <stdlib.h>
#include <time.h>

const int POCET_STRAN_KOCKY = 6;
typedef struct kocka {
    int hod;
} KOCKA;

KOCKA *Kocka();
void Kocka_free(KOCKA *kocka);
void hodKockou(KOCKA *kocka);
void vynulujKocku(KOCKA *kocka);
int generujHod();
int getHodeneCislo(KOCKA *kocka);


#endif //POSKOSEMESTRALNAPRACA_KOCKA_H
