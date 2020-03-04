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

typedef struct ember * e_pointer;

typedef struct embersor {
    int size;    
    ember ember[5];
} embersor;

typedef struct embersor * es_pointer;

es_pointer letrehoz (int alloc_size)
{    
    es_pointer x = malloc( sizeof(embersor) * alloc_size);
    x->size = 0;
    return x;
}

int ures (es_pointer e)
{
    return (e->size == 0)?1:0;
}

int tele (es_pointer e)
{
    return (e->size == 5)?1:0;
}

void ragaszt(es_pointer e, ember uj)
{
    if (!tele(e))
    {        
        strcpy(e->ember[e->size].nev, uj.nev);
        e->ember[e->size].kor = uj.kor;
        e->size++;
    }
}

ember kivesz(es_pointer e)
{
    ember kivett_e = {};
    if (!ures(e))
    {
        kivett_e = e->ember[0];
        for (int i=0; i<e->size-1; i++)
            e->ember[i] = e->ember[i+1];
        e->size--;
    }
    return kivett_e;
}

void kiir(es_pointer e)
{
    for (int i=0; i<e->size; i++)
        printf("%s - %d\n", e->ember[i].nev, e->ember[i].kor);
    printf("\n");
}

void felszabadit(es_pointer e)
{
    free(e);
}

int main()
{    
    es_pointer embersor = letrehoz(5);
    ember uj;
    ember kivett;

    kiir(embersor);

    strcpy(uj.nev,"1");
    uj.kor = 11;
    ragaszt(embersor,uj);

    strcpy(uj.nev,"2");
    uj.kor = 22;
    ragaszt(embersor,uj);

    strcpy(uj.nev,"3");
    uj.kor = 33;
    ragaszt(embersor,uj);

    kiir(embersor);

    kivett = kivesz(embersor);
    printf("Kivett:\n%s - %d \n\n", kivett.nev, kivett.kor);

    kiir(embersor);

    printf("Kivett:\n%s - %d\n\n", kivesz(embersor).nev); // valamiert kiirja a nevet es a kort is

    kiir(embersor);

    return 0;
}
/*
int main()
{

}
*/
