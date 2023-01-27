#include "kocka.h"

const int POCET_STRAN_KOCKY = 6;

KOCKA *Kocka() {
    KOCKA *kocka = malloc(sizeof(KOCKA));
    if (kocka == NULL)
        return NULL;
    kocka->hod = 0;
    return kocka;
}

void Kocka_free(KOCKA *kocka) {
    free(kocka);
}

void vynulujKocku(KOCKA *kocka) {
    kocka->hod = 0;
}

int generujHod() {
    return rand() % POCET_STRAN_KOCKY + 1;
}
void hodKockou(KOCKA *kocka) {
    kocka->hod = generujHod();
}

int getHodeneCislo(KOCKA *kocka) {
    return kocka->hod;
}
