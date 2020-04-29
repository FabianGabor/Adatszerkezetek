#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
                /*
                if (atoi(ptr) >0)
                    data_tmp[i] = atoi(ptr);
                else
                    data_tmp[i] = (*ptr - 'A');

                ptr = strtok(NULL, delim);
                */
                szemelyek[i].szulDatum.ev = atoi(ptr);
                ptr = strtok(NULL, delim);
                szemelyek[i].szulDatum.ho = atoi(ptr);
                ptr = strtok(NULL, delim);
                szemelyek[i].szulDatum.nap = atoi(ptr);

                char delim[] = "\0"; // innentol a vegeig, ujradeklaralva, hogy while cikluson kivul alljon vissza " "-re
                ptr = strtok(NULL, delim);
                strcpy(szemelyek[i].nev, ptr);

                printf("%s", szemelyek[i].nev);
                i++;
                ptr = NULL;
            }
        }
        fclose (file);
    }

    return NULL;
}

int main()
{
    lista szemelyek;
    szemelyek = letrehoz("in.txt");

    return 0;
}
