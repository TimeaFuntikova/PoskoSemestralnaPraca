#include "hrac.h"
const int POCET_PANACIKOV = 4;

HRAC *hrac(int id, FARBA_HRACA farba) {
    HRAC *hrac = malloc(sizeof(HRAC));
    if (hrac == NULL)
        return NULL;
    hrac->idHraca = id;
    hrac->farbaHraca = farba;
    hrac->maPanacikaNaDrahe = false;
    hrac->maVsetkyPanacikyVCieli = false;
    hrac->pocetHodovKocky = 0;
    //nacitajPanacikovHraca(hrac);
    printf("Hrac sa vytvoril.\n");
    return hrac;

}

void Hrac_free(HRAC *hrac) {
    free(hrac);
}

int dajIndexPanacika(HRAC *hrac, int idPanacika_) {
    for (int i = 0; i < sizeof(hrac->panaciky); ++i) {
        if(hrac->panaciky[i].idPanacikaPanacik == idPanacika_) {
            return i;
        }
    } return -1;
}
PANACIK* dajAktualnehoPanacika(HRAC *hrac, int idPanacik_) {
    int index = dajIndexPanacika(hrac, hrac->idAktualnyPanacik);
    if (hrac->panaciky != NULL && index > -1 && index < sizeof(hrac->panaciky)) {
        return &(hrac->panaciky[index]);
    } else { return NULL; }
}

void posunPanacika(HRAC *hrac, PANACIK *p, int cisloHoduKocky_) {
    if (p != NULL && pripocitajPrejdenePolicka(p,cisloHoduKocky_)) {
        for(int i = 0; i < cisloHoduKocky_; ++i) {
            int x = p->poziciaX;
            int y = p->poziciaY;
            int posunVodorovne = 0;
            int posunZvislo = 0;
            if (y == 4 && (x >= 0 && x < 4 || x >= 6 && x < 10)) {
                posunVodorovne = 1;
            }

            if (y == 6 && (x > 0 && x <= 4 || x > 6 && x <= 10)) {
                posunVodorovne = -1;
            }

            if (y == 0 && x >= 4 && x < 6) {
                posunVodorovne = 1;
            }

            if (y == 10 && x > 4 && x <= 6) {
                posunVodorovne = -1;
            }

            if (x == 6 && (y >= 0 && y < 4 || y >= 6 && y < 10)) {
                posunZvislo = 1;
            }

            if (x == 4 && (y > 0 && y <= 4 || y > 6 && y <= 10)) {
                posunZvislo = -1;
            }

            if (x == 10 && y >= 4 && y < 6) {
                posunZvislo = 1;
            }

            if (x == 0 && y > 4 && y <= 6) {
                posunZvislo = -1;
            }
            posunPanacikaPanacik(p,posunVodorovne, posunZvislo);
        }
    }
}

void nastavitPanacikaNaStart(HRAC *hrac, PANACIK *p) {
    int x = 0;
    int y = 0;
    if (p->idHracaPanacik == 1) {
        x = 0;
        y = 4;
    }

    if (p->idHracaPanacik == 2) {
        x = 6;
        y = 0;
    }

    if (p->idHracaPanacik == 3) {
        x = 4;
        y = 10;
    }

    if (p->idHracaPanacik == 4) {
        x = 10;
        y = 6;
    }

    nastavPanacikaNaStartovaciuPoziciu(p,x, y);
    hrac->maPanacikaNaDrahe = true;
}


void nasledujuciPanacik(HRAC *hrac) {
    int maxIndex = sizeof(hrac->panaciky) - 1;
    hrac->maPanacikaNaDrahe = false;
    if (hrac->panaciky != NULL) {
        int idPoslednehoPanacika = hrac->panaciky[maxIndex].idPanacikaPanacik;
        if (hrac->idAktualnyPanacik < idPoslednehoPanacika) {
            ++hrac->idAktualnyPanacik;
        } else {
            hrac->idAktualnyPanacik = -1;
        }
    }
}

void vyhoditPanacika(HRAC *hrac, PANACIK *panacik) {
    nastavDomovPanacika(hrac, panacik);
}

void nastavitPanacikaDoCiela(HRAC *hrac, PANACIK *panacik) {
    if (panacik != NULL) {
        int x = 0;
        int y = 0;
        switch (panacik->idHracaPanacik) {
            case 1:
                x = 5 - panacik->idPanacikaPanacik;
                y = 5;
                break;
            case 2:
                x = 5;
                y = 5 -panacik->idPanacikaPanacik;
                break;
            case 3:
                x = 5;
                y = 5 + panacik->idPanacikaPanacik;
                break;
            case 4:
                x = 5 + panacik->idPanacikaPanacik;
                y = 5;
        }

        nastavPanacikaNaCielovuPoziciu(panacik, x, y);
        hrac->maPanacikaNaDrahe = false;
        nasledujuciPanacik(hrac);
        if (hrac->idAktualnyPanacik == -1) {
            hrac->maVsetkyPanacikyVCieli= true;
        }
    }
}

PANACIK* zoberPanacika(HRAC *hrac) {
    int index = dajIndexPanacika(hrac,hrac->idAktualnyPanacik);
    if(index > -1) {
        return &(hrac->panaciky[index]);
    } else {
        return NULL;
    }
}

void nacitajPanacikovHraca(HRAC *hrac) {

    PANACIK * p = Panacik_new(hrac->idAktualnyPanacik,hrac->idHraca, hrac->farbaHraca);

    for(int i = 0; i < hrac->POCET_PANACIKOV; i++) {

        int idPanacika = i + 1;
        hrac->panaciky[i] = *p;
        hrac->panaciky[i].idPanacikaPanacik = idPanacika;
        hrac->panaciky[i].idHracaPanacik = hrac->idHraca;
        hrac->panaciky[i].farbaHraca = hrac->farbaHraca;
        nastavDomovPanacika(hrac, &(hrac->panaciky[i]));
    }
    hrac->idAktualnyPanacik = hrac->panaciky[0].idPanacikaPanacik;
}

void zmazVsetkychPanacikov(HRAC *hrac) {

        for (int i = 0; i < hrac->POCET_PANACIKOV; i++) {
            zmazPanacika(&(hrac->panaciky[i]));//zmaze instancie

        free(hrac->panaciky); //uvolni pamat pola kde boli uchovane panaciky
    }
    hrac->maPanacikaNaDrahe = false; //signal aborted - lebo hrac este neexistuje!
}

void nastavDomovPanacika(HRAC *hrac,PANACIK *panacik) {
    int x = 0;
    int y = 0;
    if (panacik != NULL) {
        if (panacik->idPanacikaPanacik > 2) {
            y = 1;
        }

        if (panacik->idPanacikaPanacik == 2 || panacik->idPanacikaPanacik == 4) {
            x = 1;
        }

        if (panacik->idHracaPanacik == 2) {
            x += 9;
        }

        if (panacik->idHracaPanacik == 3) {
            y += 9;
        }

        if (panacik->idHracaPanacik == 4) {
            x += 9;
            y += 9;
        }

        nastavPanacikaNaDomovskuPoziciu(panacik, x, y);
        hrac->maPanacikaNaDrahe = false;
    }
}

    void vypisStavHrac(HRAC *hrac) {
        int var10000 = hrac->idHraca;
        //toto dat do premennej
        printf("hráč č. %d, s farbou: %d \n", var10000, hrac->farbaHraca);

        if (hrac->maVsetkyPanacikyVCieli) {
            printf("hráč č. %d, s farbou: %d  má všetky panáčiky v cieli !\n", var10000, hrac->farbaHraca);
            printf("-------   HURÁ -------\n");
        } else {
            PANACIK *p = zoberPanacika(hrac);
            if (p != NULL) {
                vypisStavPanacik(p);
            } else {
                printf("Panacik_new nie je dostupny!");
            }
        }
    }

        void hodilKocku(HRAC *hrac) {
            hrac->pocetHodovKocky++;
        }

        void vynulujPocetHodovKocky(HRAC *hrac) {
        hrac->pocetHodovKocky = 0;
        }
