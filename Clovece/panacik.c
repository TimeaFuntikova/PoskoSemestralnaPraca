#include "panacik.h"
#include <stdio.h>

PANACIK *Panacik(int idPanacika_, int idHraca_, FARBA_HRACA farbaHraca_) {
    PANACIK *panacik = malloc(sizeof(PANACIK)); //problem s implicitnou deklaraciou pre malloc
    if (panacik == NULL)
        return NULL;
    panacik->idHracaPanacik = idHraca_;
    panacik->idPanacikaPanacik = idPanacika_;
    panacik->farbaHraca = farbaHraca_;
    panacik->stavPanacika = NEDEFINOVANY;
    nastavObrazok(panacik);

    return panacik;
}
void Panacik_free(PANACIK *panacik) {
    free(panacik);
}
int getIdHraca(PANACIK *panacik) {return panacik->idHracaPanacik;}
int getPocetPrejdenychPolicok(PANACIK *p) {return p->pocetPrejdenychPolicok;}
int getIdPanacika(PANACIK *p){return p->idPanacikaPanacik;}
int getPoziciaX(PANACIK *p){return p->poziciaX;}
int getPoziciaY(PANACIK *p){return p->poziciaY;}
bool jeNaKonci(PANACIK *p){return p->pocetPrejdenychPolicok >= 39;}
bool jePredCielom(PANACIK *p, int pocetNaKocke){return p->pocetPrejdenychPolicok + pocetNaKocke >= 39;}



bool pripocitajPrejdenePolicka(PANACIK *p, int pocetNaKocke){
    int poziciaVCieli = 4 - getIdPanacika(p);
    if(getPocetPrejdenychPolicok(p) < 40 + poziciaVCieli) {
        p->pocetPrejdenychPolicok += pocetNaKocke;
        return true;
    } else {
        return false;
    }
}
void nastavPoziciu(PANACIK *p, int pX_, int pY_) {
    p->poziciaX= pX_;
    p->poziciaY= pY_;
}

void nastavPanacikaNaPoziciu(PANACIK *p, int pX_, int pY_) {
    nastavPoziciu(p,pX_,pY_);


}
void nastavPanacikaNaDomovskuPoziciu(PANACIK *p, int pX_, int pY_){
    nastavPanacikaNaPoziciu(p,pX_,pY_);
    p->stavPanacika = JE_DOMA;
}

void nastavPanacikaNaNovuPoziciu(PANACIK *p, int pX_, int pY_){
    nastavPanacikaNaPoziciu(p,pX_,pY_);
    p->stavPanacika = JE_NA_DRAHE;
}

void nastavPanacikaNaStartovaciuPoziciu(PANACIK *p, int pX_, int pY_){
    nastavPanacikaNaPoziciu(p,pX_,pY_);
    p->stavPanacika = JE_NA_STARTE;
}

void nastavPanacikaNaCielovuPoziciu(PANACIK *p, int pX_, int pY_){
    nastavPanacikaNaPoziciu(p,pX_,pY_);
    p->stavPanacika = JE_V_CIELI;
}
 void posunPanacikaPanacik(PANACIK *p, int posunVodorovne, int posunZvislo) {
    int novaPoziciaX = p->poziciaX + posunVodorovne;
    int novaPoziciaY = p->poziciaY + posunZvislo;
     nastavPanacikaNaPoziciu(p, novaPoziciaX, novaPoziciaY);
}

void nastavObrazok(PANACIK *panacik) {
    if(panacik->farbaHraca != NULL) {
        switch (panacik->farbaHraca) {
            case ZELENA:
                (*panacik->obrazok.o )= 'g';
            case MODRA:
                (*panacik->obrazok.o )= 'b';
            case ZLTA:
                (*panacik->obrazok.o )= 'y';
            case CERVENA:
                (*panacik->obrazok.o )= 'r';
            default:
                printf("NEDEFINOVANE, INTERNAL ERROR\n");
        }
    }
}

void zmazPanacika(PANACIK *p){
    Panacik_free(p);
}

//metody na vypis o priebehu hry pre spravu servera a klienta - Poriesit ako sa toto dostane ku serveru
  void vypisStavPanacik(PANACIK *p) {
    switch (p->stavPanacika) {
        case JE_NA_STARTE:
            printf("panáčik č. %d (X= %d , Y= %d ... JE NA STARTE.)\n", p->idPanacikaPanacik, p->poziciaX, p->poziciaY);
            break;
        case JE_V_CIELI:
            printf("panáčik č. %d (X= %d , Y= %d ... JE V CIELI.)\n", p->idPanacikaPanacik, p->poziciaX, p->poziciaY);
            break;
        default:
            if (p->pocetPrejdenychPolicok> 0) {
                printf("panáčik č. %d (X= %d , Y= %d ... presiel %d policok.)\n", p->idPanacikaPanacik, p->poziciaX, p->poziciaY, p->pocetPrejdenychPolicok);
            }
    }
}


