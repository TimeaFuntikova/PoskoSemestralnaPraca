#include "hraClovece.h"

HRA_CLOVECE *hra() {
    HRA_CLOVECE *hra = malloc(sizeof(HRA_CLOVECE));
    if (hra == NULL)
        return NULL;
    nacitajHraciuPlochu(&(hra->plocha));
    novaHra(hra);
}

void Hra_free(HRA_CLOVECE *hra) {
    free(hra);
}

void pokracovatHodomKocky(HRA_CLOVECE *hra, KOCKA *k) {
    if(hra->hraPrebieha) {
        hodKockou(k);
    }
}

void clear(HRA_CLOVECE *hra) {

        for (int i = 0; i < sizeof(hra->hraci); ++i) {
            zmazVsetkychPanacikov(&hra->hraci[i]);
        }
        //zmaz hracov a kocku a plochu a hru a vobec vsetko
        //hra->hraci = NULL;

    //hra->aktualnyHrac = NULL;
    hra->pocetHracov = 0;
}

int dajIndexHraca(HRA_CLOVECE *hra, int idAktualnyHrac_)
 {
    for (int i = 0; i < sizeof (hra->hraci); ++i) {
        if(hra->hraci[i].idHraca == idAktualnyHrac_) {
            return i;
        }
    }
}

void nasledujuciHrac(HRA_CLOVECE *hra) {
    int maxIndex = sizeof(hra->hraci) - 1;
    int idAktualnyHrac = -1;
    int idPoslednehoHraca = hra->hraci[maxIndex].idHraca;
    idAktualnyHrac = hra->aktualnyHrac.idHraca;

    int idx;
    if(idAktualnyHrac < idPoslednehoHraca) {
        ++idAktualnyHrac;
        idx = dajIndexHraca(hra, idAktualnyHrac);

    }else {
        idx = 0;
    }

    hra->aktualnyHrac = hra->hraci[idx];
    //vypisStav();
}


HRAC dajVolnehoHraca(HRA_CLOVECE *hra) {
    HRAC hrac = hra->aktualnyHrac;
    if(hrac.maVsetkyPanacikyVCieli) {
        nasledujuciHrac(hra);
        return dajVolnehoHraca(hra);
    } else {
        return hrac;
    }
}

void novaHra(HRA_CLOVECE *hra) {
    clear(hra);
    nastavPocetHracov(hra);

    while(hra->pocetHracov < 1 || hra->pocetHracov > 4) {
        nastavPocetHracov(hra);
    }
    zacniHru(hra);
}

void nastavPocetHracov(HRA_CLOVECE *hra) {
    int zadanyPocetHracov = 0;
    int min = 0;
    while(zadanyPocetHracov <= min) {
        printf("Zadaj pocet hracov: ");
        scanf("%d", &zadanyPocetHracov);
        printf("Number = %d\n", zadanyPocetHracov);
        hra->pocetHracov = zadanyPocetHracov;
    }
    printf("Nastavil sa pocet hracov = %d\n", zadanyPocetHracov);
}

void nacitajHracov(HRA_CLOVECE *hra) {
    FARBA_HRACA farba = 0;
    for (int i = 0; i < MAX_POCET_HRACOV; ++i) {
        int idHraca = i+1;
        if(idHraca ==1) {
            farba = ZELENA;
        } if(idHraca ==2) {
            farba = MODRA;
        }
        if(idHraca ==3) {
            farba = CERVENA;
        }
        if(idHraca ==4) {
            farba = ZLTA;
        }

        if(idHraca > 0 && farba != NULL) {
            hra->hraci[i] = *(hrac(idHraca,farba));
        }
    } hra->aktualnyHrac = hra->hraci[0];
}

HRAC vratHracaNaRovnakejPozicii(HRA_CLOVECE *hra, PANACIK *p) {
    for (int i = 0; i < sizeof(hra->hraci); ++i) {
        HRAC inyHrac = hra->hraci[i];
        if(inyHrac.idHraca != p->idHracaPanacik) {
            PANACIK *inyPanacik = zoberPanacika(&inyHrac);
            if(inyPanacik->poziciaX == p->poziciaX && inyPanacik->poziciaY == p->poziciaY) {
                return inyHrac;
            }
        }
    }
}

void skontrolujNovuPoziciuPanacika(HRA_CLOVECE *hra, PANACIK *panacik) {
    HRAC konfliktnyHrac = vratHracaNaRovnakejPozicii(hra, panacik);
    PANACIK *konfliktnyPanacik = zoberPanacika(&konfliktnyHrac);
    vyhoditPanacika(&konfliktnyHrac,konfliktnyPanacik);
    //vypisStav
}

void nastavNaStart(HRAC *hrac) {
    PANACIK *p = zoberPanacika(hrac);
    nastavitPanacikaNaStart(hrac,p);
}

void vyhodPanacika(HRAC *hrac) {
    PANACIK *p = zoberPanacika(hrac);
    vyhoditPanacika(hrac,p);
}

void zacniHru(HRA_CLOVECE *hra) {
    hra->hraPrebieha = true;
    nacitajHracov(hra);
    //vypisStav();
    pokracovatHodomKocky(hra, &(hra->kocka));
}

void koniecHry(HRA_CLOVECE *hra) {
    uvolniPamat(hra);
    if(hra->hraPrebieha) {
        hra->hraPrebieha = false;
        printf("-------Koniec hry---------.\n");
        exit(0);
    }
}

void uvolniPamat(HRA_CLOVECE *hra) {
    zmazVsetkychPanacikov(hra->hraci);
    Kocka_free(&hra->kocka);
    Hrac_free(hra->hraci);
    Plocha_free(&hra->plocha);
    Hra_free(hra);
    printf("Pamat sa uvlolnila.\n"); //aspon teoreticky lol
}

void hodKocku(HRA_CLOVECE *hra) {
    if (hra->hraPrebieha) {
        char potvrdenie = ' ';
        printf("stlac h pre hod kockou: \n");
        scanf("%c", &potvrdenie);

        if (potvrdenie == 'h') {
            printf("Uskutocnil sa hod.\n");
            tahHraca(hra,getHodeneCislo(&hra->kocka));
        }
        printf("HRA SA KONCI.\n");
        koniecHry(hra);
    }
}

void tahHraca(HRA_CLOVECE *hra, int hodeneCisloNaKocke) {
    hodilKocku(&hra->aktualnyHrac);
    PANACIK *panacik = zoberPanacika(&hra->aktualnyHrac);
    if (hra->aktualnyHrac.maPanacikaNaDrahe) {
        if (jePredCielom(panacik, hodeneCisloNaKocke)) {
            nastavitPanacikaDoCiela(&hra->aktualnyHrac, panacik);
            printf("PANACIK JE V CIELI : %d\n", hra->aktualnyHrac.idHraca);
        } else {
            posunPanacika(&hra->aktualnyHrac, panacik, hodeneCisloNaKocke);
            printf("POSUN: %d pre hraca s id: %d\n", hodeneCisloNaKocke, hra->aktualnyHrac.idHraca);
            skontrolujNovuPoziciuPanacika(hra, panacik);
        }
        vynulujKocku(&hra->kocka);
        vynulujPocetHodovKocky(&hra->aktualnyHrac);
        nasledujuciHrac(hra);
    } else if (hra->aktualnyHrac.pocetHodovKocky <= 3) {
        if (hodeneCisloNaKocke == 6) {
            nastavitPanacikaNaStart(&hra->aktualnyHrac, panacik);
            printf("PANACIK SA NASTAVIL NA START: id hraca = %d\n", hra->aktualnyHrac.idHraca);
        } else {
            printf("NEUSPESNY HOD  pokus č. %d pre hraca s id = %d\n", hra->aktualnyHrac.pocetHodovKocky,
                   hra->aktualnyHrac.idHraca);

        }
    } else {
        nasledujuciHrac(hra);
        if (!hra->aktualnyHrac.maVsetkyPanacikyVCieli) {
            tahHraca(hra, hodeneCisloNaKocke);
        }
        koniecHry(hra);
    }
    pokracovatHodomKocky(hra,&(hra->kocka));
}


