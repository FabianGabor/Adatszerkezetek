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
} * szekreny;

void kiir(szekreny sz);

int main() {
    szekreny szekreny = malloc(sizeof(struct szekreny));

    szekreny->db = 2; // szekrenyek szama
    szekreny->fiokSzam[0].db = 2; // 0. szekreny fiokok szama

    strcpy(szekreny->fiokSzam[0].fajtaSzam[0].fajta, "reszelo");
    szekreny->fiokSzam[0].fajtaSzam[0].db = 3;
    strcpy(szekreny->fiokSzam[0].fajtaSzam[1].fajta, "harapofogo");
    szekreny->fiokSzam[0].fajtaSzam[1].db = 4;

    szekreny->fiokSzam[1].db = 1; // 0. szekreny fiokok szama
    strcpy(szekreny->fiokSzam[1].fajtaSzam[0].fajta, "reszelo");
    szekreny->fiokSzam[1].fajtaSzam[0].db = 2;

    kiir(szekreny);

    return 0;
}

void kiir(szekreny sz) {
    for (int szekreny = 0; szekreny < sz->db; szekreny++) {
        printf("%d fiok: \n", szekreny);
        for (int fiok = 0; fiok < sz->fiokSzam[szekreny].db; fiok++)
            printf("%s %d db\n", sz->fiokSzam[szekreny].fajtaSzam[fiok].fajta, sz->fiokSzam[szekreny].fajtaSzam[fiok].db);
        printf("\n");
    }
    printf("\n");
}