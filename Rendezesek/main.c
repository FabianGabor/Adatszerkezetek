#include <stdio.h>

typedef struct szulDatum {
    unsigned int ev;
    unsigned int honap;
    unsigned int nap;
} szuletesiDatum;

typedef struct szemely {
    char nev[30];
    szuletesiDatum szulDatum;
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
    printf("%s", allomanynev);

    FILE *file;
    file = fopen(allomanynev, "r");

    char str[9999];

    if (file == NULL) perror ("Fajl nyitasi hiba");
    else
    {
        while( fgets(str, 9999, file) != NULL )
        {
            printf("%s\n", str);
        }
        fclose (file);
    }

    return NULL;
}

int main()
{
    lista lista;
    lista = letrehoz("in.txt");

    return 0;
}
