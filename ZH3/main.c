#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Egy szekrenynek 3 fiokja van,
 mindegyikben maximum 6 darab egyforma fajta szerszam fer el.

 A szerszamoknak van fajtaja (max. 10db angol
abc-ebeli kisbetu, melyet karakterekbol allo tombben tarolunk)
 */

typedef struct szerszam {
    char fajta[10];
    int db;
} szerszam;

typedef struct fiok {
    szerszam fajtaSzam[6];
    int db;
} fiok;

typedef struct szekreny {
    fiok fiokSzam[3];
    int db;
} szekreny;

void kiir(szekreny sz);
int mennyi_ures_fiok(szekreny sz);

int main() {
    szekreny szekreny;
    szekreny.fiokSzam[0].db = 3; // 0. szekreny fiokok szama

    for (int i=0; i<3; i++) {
        szekreny.fiokSzam[i].db = 3;
        for (int j=0; j<6; j++) {
            szekreny.fiokSzam[i].fajtaSzam[j].db = 0;
        }
    }

    strcpy(szekreny.fiokSzam[0].fajtaSzam[0].fajta, "reszelo");
    szekreny.fiokSzam[0].fajtaSzam[0].db = 3;
    strcpy(szekreny.fiokSzam[0].fajtaSzam[1].fajta, "harapofogo");
    szekreny.fiokSzam[0].fajtaSzam[1].db = 4;

    szekreny.fiokSzam[1].db = 3; // 1. szekreny fiokok szama
    strcpy(szekreny.fiokSzam[1].fajtaSzam[0].fajta, "reszelo");
    szekreny.fiokSzam[1].fajtaSzam[0].db = 2;

    kiir(szekreny);
    printf("Ures fiokok szama: %d \n", mennyi_ures_fiok(szekreny));

    return 0;
}

void kiir(szekreny sz) {
    for (int fiok = 0; fiok < sz.fiokSzam->db; fiok++) {
        printf("%d fiok: \n", fiok);
        for (int szerszam = 0; szerszam < sz.fiokSzam[fiok].db; szerszam++)
            if (sz.fiokSzam[fiok].fajtaSzam[szerszam].db > 0)
                printf("%s %d db\n", sz.fiokSzam[fiok].fajtaSzam[szerszam].fajta, sz.fiokSzam[fiok].fajtaSzam[szerszam].db);
        printf("\n");
    }

    printf("\n");
}

int mennyi_ures_fiok(szekreny sz) {
    int ures = 0;
    int nincsszerszam = 1;
    for (int fiok = 0; fiok < sz.fiokSzam->db; fiok++) {
        for (int szerszam = 0; szerszam < sz.fiokSzam[fiok].db; szerszam++)
            if (sz.fiokSzam[fiok].fajtaSzam[szerszam].db > 0) { // itt kell még debuggolni
                nincsszerszam = 0;
            }
        if (nincsszerszam > 0) ures++;
    }
    return ures;
}
