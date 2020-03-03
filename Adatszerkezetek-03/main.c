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
} embersor;

typedef struct embersor * es_pointer;

es_pointer letrehoz ()
{
    es_pointer x = malloc( sizeof(embersor) * 5 );
    return x;
}

int ures (embersor e)
{
    return (e.size == 0)?1:0;
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

void kiir(es_pointer e)
{
    for (int i=0; i<e->size; i++)
        printf("%s - %d\n", e->ember[i].nev, e->ember[i].kor);
}

int main()
{    
    es_pointer embersor = letrehoz();
    ember uj;

    kiir(embersor);
    strcpy(uj.nev,"Teszt ember");
    uj.kor = 33;

    ragaszt(embersor,uj);
    kiir(embersor);
    return 0;
}
/*
int main()
{

}
*/
