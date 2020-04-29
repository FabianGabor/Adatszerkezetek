#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*
Személyek adatait tartjuk nyilván: név (max. 29 karakter, szóközt is tartalmazhat), születési év, hónap, nap.
Maximum 10 személy adatait kell tárolnunk. Írja meg a lista, szemely , ev, ho, nap, szuldatum, nev típusokat,
ahol a lista tartalmazza a személyeket, melyek tartalmazzák a nevet és a szuldatumot, ahol utóbbi tartalmazza az
év, ho, nap típusokat. Írja meg a lista letrehoz(char * allomanynev) függvényt, mely a megadott állományból
képes feltölteni a listát. Az állomány soronként egy személy adatait tartalmazza a következőképpen:
*/

typedef unsigned int ev;
typedef unsigned int ho;
typedef unsigned int nap;

typedef struct szulDatum {
    ev ev;
    ho ho;
    nap nap;
} szuldatum;

typedef struct szemely {
    char nev[30];
    szuldatum szulDatum;
} szemely;

typedef szemely *lista;
typedef char allomanynev[30];

void beilleszteses(int *t, int n)
{
    int i, j, cs;
    for (i = 1; i < n; i++) {
        cs = t[i];
        j = i - 1;
        while (j >= 0 && t[j] > cs) {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = cs;
    }
}


lista letrehoz(char * allomanynev)
{
    FILE *file;
    file = fopen(allomanynev, "r");

    char str[30];
    int i=0;
    char delim[] = " ";
    char *ptr;

    lista szemelyek = malloc(sizeof(szemelyek) * 10);

    if (file == NULL) perror ("Fajl nyitasi hiba");
    else
    {
        while( fgets(str, 9999, file) != NULL )
        {
            //printf("%s\n", str);

            i=0;
            ptr = strtok(str, delim);
            while(ptr != NULL)
            {
                szemelyek[i].szulDatum.ev = atoi(ptr);
                ptr = strtok(NULL, delim);
                szemelyek[i].szulDatum.ho = atoi(ptr);
                ptr = strtok(NULL, delim);
                szemelyek[i].szulDatum.nap = atoi(ptr);

                char delim[] = "\0"; // innentol a vegeig, ujradeklaralva, hogy while cikluson kivul alljon vissza " "-re
                ptr = strtok(NULL, delim);

                while (ptr[strlen(ptr)-1] == '\r' || ptr[strlen(ptr)-1] == '\n') // Unix/Linux eseten '\n' a sorveg, Win eseten '\r\n', Mac eseten '\r'
                    ptr[strlen(ptr)-1] = 0;


                strcpy(szemelyek[i].nev, ptr);

                printf("%s %d %d %d \n", szemelyek[i].nev, szemelyek[i].szulDatum.ev, szemelyek[i].szulDatum.ho, szemelyek[i].szulDatum.nap);
                i++;
                ptr = NULL;
            }
        }
        fclose (file);
    }

    return NULL;
}
//rendezesimezo értéke a következők egyike lehet: "szuldatum", "nev", ha az irany 1, akkor novekvobe, ha nulla, akkor pedig csökkenőbe rendez.
lista rendez(char * rendezesimezo, int irany);

int main()
{
    lista szemelyek;
    szemelyek = letrehoz("in.txt");

    return 0;
}
