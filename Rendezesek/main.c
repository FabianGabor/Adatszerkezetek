#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ThreeWayRadixQSort.h>

#define MAX_SZEMELYEK 10

/*
Személyek adatait tartjuk nyilván: név (max. 29 karakter, szóközt is tartalmazhat), születési év, hónap, nap.
Maximum 10 személy adatait kell tárolnunk. Írja meg a lista, szemely , ev, ho, nap, szuldatum, nev típusokat,
ahol a lista tartalmazza a személyeket, melyek tartalmazzák a nevet és a szuldatumot, ahol utóbbi tartalmazza az
év, ho, nap típusokat. Írja meg a lista letrehoz(char * allomanynev) függvényt, mely a megadott állományból
képes feltölteni a listát. Az állomány soronként egy személy adatait tartalmazza a következőképpen:
*/

typedef char nev[30];
typedef unsigned int ev;
typedef unsigned int ho;
typedef unsigned int nap;

typedef struct szulDatum {
    ev ev;
    ho ho;
    nap nap;
} szuldatum;

typedef struct szemely {
    nev nev;
    szuldatum szulDatum;
} szemely;

typedef szemely *lista;
typedef char allomanynev[30];

lista letrehoz(char * allomanynev);
//rendezesimezo értéke a következők egyike lehet: "szuldatum", "nev", ha az irany 1, akkor novekvobe, ha nulla, akkor pedig csökkenőbe rendez.
lista rendez(lista szemelyek, char * rendezesimezo, int irany);
void kiir(lista szemelyek);


int main()
{
    lista szemelyek = malloc(sizeof (*szemelyek) * MAX_SZEMELYEK);
    szemelyek = letrehoz("in.txt");
    szemelyek = rendez(szemelyek, "nev", 1);
    kiir(szemelyek);

    return 0;
}

lista letrehoz(char * allomanynev)
{
    FILE *file;
    file = fopen(allomanynev, "r");


    char str[30];
    char delim[] = " ";
    char *ptr;

    int i=0;

    lista szemelyek = malloc(sizeof(*szemelyek) * MAX_SZEMELYEK);

    if (file == NULL) perror ("Fajl nyitasi hiba");
    else
    {
        //while( fgets(str, 9999, file) != NULL )
        while (fscanf(file, "%ul", &szemelyek[i].szulDatum.ev) != EOF)
        {
            fscanf(file, "%ul", &szemelyek[i].szulDatum.ho);
            fscanf(file, "%ul", &szemelyek[i].szulDatum.nap);
            fscanf(file, "%s", NULL); // nap es nev kozotti szokoz
            fgets(szemelyek[i].nev, sizeof (szemelyek[i].nev), file);
            i++;
        }
        fclose (file);
    }
    return szemelyek;
}

lista rendez (lista szemelyek, char * rendezesimezo, int irany) {
    irany = 0; // remove unused warning temporarily
    if (strcmp(rendezesimezo, "nev") == 0)
    {
        printf("Nev szerinti rendezes\n");
        //sortString();
    }
    else if (strcmp(rendezesimezo, "szuldatum") == 0)
    {
        printf("Szuletesi datum szerinti rendezes\n");
    }

    return szemelyek;
}

void kiir(lista szemelyek)
{
    for (unsigned int i=0; i<5; i++)
        printf("%s \t%d.%d.%d.\n", szemelyek[i].nev, szemelyek[i].szulDatum.ev, szemelyek[i].szulDatum.ho, szemelyek[i].szulDatum.nap);
}
