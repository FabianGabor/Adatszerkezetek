/*
embersor
    nev [29], kor

linearis adatszerkezet
    0-5 ember

muveletek
    kiveszi az elso embert es visszaadja
    ragaszt: jobbrol hozzaad egy ujat
    letrehoz: ures embersort hoz letre
    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct ember {
    char nev[30];
    int kor;
} ember;

typedef struct embersor {
    int size;
    ember ember[5];
} es;

typedef struct es * embersor;

embersor letrehoz ()
{
    embersor x = malloc( sizeof(es) * 5 );
    return x;
}

int ures (es e)
{
    return (e.size == 0)?1:0;
}

int tele (es *e)
{
    return (e->size == 5)?1:0;
}

void ragaszt(es *e, ember uj)
{
    if (!tele(e))
    {
        e->size++;
        strcpy(e->ember[e->size].nev, uj.nev);
        e->ember[e->size].kor = uj.kor;
    }
}

void kiir(es e)
{
    /*
    for (int i=0; i<e.size; i++)
    {
        printf("%s", e.ember[i].nev);
    }
    */
}

int main()
{
    printf("%d\n", (int) sizeof(es) * 5);
    embersor embersor = letrehoz();
    ember uj;

    kiir(embersor);
    //strcpy(uj.nev,"Teszt");
    //uj.kor = 33;

    //kiir(embersor);
    //ragaszt(embersor,uj);
    return 0;
}
