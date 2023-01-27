#include "hraciaPlocha.h"

PLOCHA *plocha() {
    PLOCHA *plocha = malloc(sizeof(PLOCHA));
    if (plocha == NULL)
        return NULL;
}

void Plocha_free(PLOCHA *plocha) {
    free(plocha);
}

void nacitajFarbyBlokov(PLOCHA *p) {
    FARBA_HRACA farba = 0;

    for (int i = 0; i < 4; ++i) {
        int idBloku = i+1;
        if(idBloku ==1) {
            farba = ZELENA;
        }
        if(idBloku ==2) {
            farba = MODRA;
        }
        if(idBloku ==3) {
            farba = CERVENA;
        }
        if(idBloku ==4) {
            farba = ZLTA;
        }
        p->farbyHracichBlokov[i] = dajFarbuPanacika(farba);
    }
}

void nacitajPlochu(PLOCHA *p) {
    //nacita sa prazdnaPlocha
    char prazdnyZnak = '-';
    int rozmer = 11;
    for (int x = 0; x < rozmer ; ++x) {
        for (int y = 0; y < rozmer ; ++y) {
            p->plocha[x][y] = prazdnyZnak;
        }
    }
}

void nacitajDrahu(PLOCHA *p) {
    char znakDrahy = 'o';

    int x;
    int y;
    for(x = 0; x < 11; ++x) {
        for(y = 4; y <= 6; ++y) {
            p->plocha[x][y] = znakDrahy;
            }
    }

    for(x = 4; x <= 6; ++x) {
        for(y = 0; y < 11; ++y) {
            p->plocha[x][y] = znakDrahy;
        }
    }
}

void nacitajBlokyHracom(PLOCHA *p) {
    for (int idBloku = 1; idBloku < sizeof*((p->farbyHracichBlokov)); ++idBloku) {
        FARBA_HRACA farbaBloku = p->farbyHracichBlokov[idBloku-1];
        nacitajStartovacieBloky(p,idBloku,farbaBloku);

        for(int idPozicie = 1; idPozicie <4; ++idPozicie) {
            nacitajDomovskeBloky(p,idBloku,idPozicie,farbaBloku);
            nacitajCieloveBloky(p, idBloku, idPozicie, farbaBloku);
        }
    }
}

void nacitajDomovskeBloky(PLOCHA *p, int idBloku, int idPozicie, FARBA_HRACA farba) {
    int x = 0;
    int y = 0;
    if (idPozicie > 2) {
        y = 1;
    }

    if (idPozicie == 2 || idPozicie == 4) {
        x = 1;
    }

    if (idBloku == 2) {
        x += 9;
    }

    if (idBloku == 3) {
        y += 9;
    }

    if (idBloku == 4) {
        x += 9;
        y += 9;
    }

    p->plocha[x][y] = dajFarbuDomu(farba);
}

void nacitajStartovacieBloky(PLOCHA *p, int idBloku, FARBA_HRACA farba) {
    int x = 0;
    int y = 0;
    if (idBloku == 1) {
        x = 0;
        y = 4;
    }

    if (idBloku == 2) {
        x = 6;
        y = 0;
    }

    if (idBloku == 3) {
        x = 4;
        y = 10;
    }

    if (idBloku == 4) {
        x = 10;
        y = 6;
    }

    p->plocha[x][y] = dajFarbuStartu(farba);
}

void nacitajCieloveBloky(PLOCHA *p, int idBloku, int idPozicie, FARBA_HRACA farba) {
    int x = 0;
    int y = 0;
    switch (idBloku) {
        case 1 :
            x = 5 - idPozicie;
            y = 5;
            break;

            case 2 :
            x = 5;
            y = 5 - idPozicie;
            break;

        case 3 :
            x = 5;
            y = 5 + idPozicie;
            break;
        case 4 :
            x = 5 + idPozicie;
            y = 5;
            break;
    }
    p->plocha[x][y] = dajFarbuDomu(farba);
}
char dajFarbuPanacika(FARBA_HRACA farba) {
        switch (farba) {
            case ZELENA:
                return 'g';
            case CERVENA:
                return 'r';
            case MODRA:
                return 'b';
            case ZLTA:
                return 'y';
            default:
                return 'm';
        }
    }

char dajFarbuStartu(FARBA_HRACA farba) {
    switch (farba) {
        case ZELENA:
            return 'G';
        case CERVENA:
            return 'R';
        case MODRA:
            return 'B';
        case ZLTA:
            return 'Y';
        default:
            return 'M';
    }
}

char dajFarbuDomu(FARBA_HRACA farba) {
    switch (farba) {
        case ZELENA:
            return 'G';
        case CERVENA:
            return 'R';
        case MODRA:
            return 'B';
        case ZLTA:
            return 'Y';
        default:
            return 'M';
    }
}

void nacitajHraciuPlochu(PLOCHA *p){
    nacitajFarbyBlokov(p);
    nacitajPlochu(p);
    nacitajDrahu(p);
    nacitajBlokyHracom(p);
}

static PLOCHA dajPlocha(){
   PLOCHA plocha = plocha;
}