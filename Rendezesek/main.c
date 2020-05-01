#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ThreeWayRadixQSort.h>
#include <TimSort.h>
#include <typedef.h>

#define MAX_SZEMELYEK 1000

/*
Személyek adatait tartjuk nyilván: név (max. 29 karakter, szóközt is tartalmazhat), születési év, hónap, nap.
Maximum 10 személy adatait kell tárolnunk. Írja meg a lista, szemely , ev, ho, nap, szuldatum, nev típusokat,
ahol a lista tartalmazza a személyeket, melyek tartalmazzák a nevet és a szuldatumot, ahol utóbbi tartalmazza az
év, ho, nap típusokat. Írja meg a lista letrehoz(char * allomanynev) függvényt, mely a megadott állományból
képes feltölteni a listát. Az állomány soronként egy személy adatait tartalmazza a következőképpen:
*/


typedef char allomanynev[30];

lista letrehoz(char * allomanynev);
//rendezesimezo értéke a következők egyike lehet: "szuldatum", "nev", ha az irany 1, akkor novekvobe, ha nulla, akkor pedig csökkenőbe rendez.
lista rendez(lista szemelyek, char * rendezesimezo, int irany);
void kiir(lista szemelyek);

unsigned int letszam = 0;

int main()
{
    lista szemelyek = malloc(sizeof (*szemelyek) * MAX_SZEMELYEK);
    szemelyek = letrehoz("MOCK_DATA.txt");

    kiir(szemelyek);
    szemelyek = rendez(szemelyek, "szuldatum", 1);
    kiir(szemelyek);

    return 0;
}

lista letrehoz(char * allomanynev)
{
    FILE *file;
    file = fopen(allomanynev, "r");

    lista szemelyek = malloc(sizeof(*szemelyek) * MAX_SZEMELYEK);

    if (file == NULL) perror ("Fajl nyitasi hiba");
    else
    {
        while (fscanf(file, "%ul", &szemelyek[letszam].szulDatum.ev) != EOF && letszam < MAX_SZEMELYEK)
        {
            fscanf(file, "%ul", &szemelyek[letszam].szulDatum.ho);
            fscanf(file, "%ul", &szemelyek[letszam].szulDatum.nap);
            fscanf(file, "%s", (char*)NULL); // nap es nev kozotti szokoz
            fgets(szemelyek[letszam].nev, sizeof (szemelyek[letszam].nev), file);
            size_t len = strlen (szemelyek[letszam].nev);
            if (len && szemelyek[letszam].nev[len-1] == '\n')
                szemelyek[letszam].nev[--len] = 0;
            if (len && szemelyek[letszam].nev[len-1] == '\r')
                szemelyek[letszam].nev[--len] = 0;

            letszam++;
        }
        fclose (file);
    }
    return szemelyek;
}

lista rendez (lista szemelyek, char * rendezesimezo, int irany) {    
    if (strcmp(rendezesimezo, "nev") == 0)
    {
        printf("*** Nev szerinti rendezes ***\n");
        sortNev(szemelyek, letszam);
        if (!irany)
            reverse(szemelyek, letszam);
    }
    else if (strcmp(rendezesimezo, "szuldatum") == 0)
    {
        printf("Szuletesi datum szerinti rendezes\n");
        timSort(szemelyek, letszam);
    }

    return szemelyek;
}

void kiir(lista szemelyek)
{
    for (unsigned int i=0; i<letszam; i++)
        printf("%s \n\t%d.%02d.%02d.\n", szemelyek[i].nev, szemelyek[i].szulDatum.ev, szemelyek[i].szulDatum.ho, szemelyek[i].szulDatum.nap);
    printf("\n");
}
