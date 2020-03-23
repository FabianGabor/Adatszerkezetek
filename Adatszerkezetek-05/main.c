#include <stdio.h>
#include <stdlib.h>>

typedef struct zacsko {
    char nev;
    int tomeg;
} zacsko;

typedef struct polc {
    zacsko polc[4];
    int darab;
} polc;

typedef struct szekreny {
    polc szekreny[8];
    int darab;
} * szekreny;

void kiir(szekreny sz) {
    for (int szekreny = 0; szekreny < sz->darab; szekreny++)
    {
        printf("\n%d polc: ", szekreny);
        for (int polc = 0; polc < sz->szekreny[szekreny].darab; polc++)
            printf("%c %d ", sz->szekreny[szekreny].polc[polc].nev, sz->szekreny[szekreny].polc[polc].tomeg);
    }
    printf("\n");
}

int betesz (polc x, szekreny sz) {

    sz->szekreny[sz->darab] = x;
    return ++sz->darab;
}

int main()
{
    szekreny szekreny = malloc(sizeof(struct szekreny));

    szekreny->darab = 2;
    szekreny->szekreny[0].darab = 2;
    szekreny->szekreny[0].polc[0].nev = 'A';
    szekreny->szekreny[0].polc[0].tomeg = 3;
    szekreny->szekreny[0].polc[1].nev = 'C';
    szekreny->szekreny[0].polc[1].tomeg = 4;

    szekreny->szekreny[1].darab = 3;
    szekreny->szekreny[1].polc[0].nev = 'B';
    szekreny->szekreny[1].polc[0].tomeg = 2;
    szekreny->szekreny[1].polc[1].nev = 'D';
    szekreny->szekreny[1].polc[1].tomeg = 5;
    szekreny->szekreny[1].polc[2].nev = 'H';
    szekreny->szekreny[1].polc[2].tomeg = 6;

    kiir(szekreny);

    polc polc;
    polc.darab = 2;
    polc.polc[0].nev = 'M';
    polc.polc[0].tomeg = 100;
    polc.polc[1].nev = 'N';
    polc.polc[1].tomeg = 1000;

    printf("\n%d", betesz(polc,szekreny) );
    kiir(szekreny);

    return 0;
}
