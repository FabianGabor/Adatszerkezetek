#include <stdio.h>
#include <stdlib.h>

typedef unsigned int azonosito;

typedef struct beteg {
    azonosito id;
    struct beteg **fertozottek;
    int fertozottek_szama;
} *beteg;


/*
typedef struct beteg{
    int data;
    struct Node *elsoFertozott;
    struct Node *tovabbiFertozott;
} beteg;
*/


typedef struct gocpont {
    beteg beteg;
} *gocpont;

gocpont uj_gocpont(beteg nulladikbeteg);
beteg uj_beteg(int azonosito);

void gocpont_torol(gocpont g);
void beteg_torol(beteg b);

int letszam(gocpont g);
int fertozottek_szama(gocpont g, beteg b);

int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott);
beteg keres(beteg fertozo, beteg keresett);
//void kiir(beteg beteg);
void kiir_gocpont(gocpont g);

int fertozott_e(gocpont g, beteg b);

int main()
{
    beteg b0, b11, b12, b13, b21,bx;
    b0 = uj_beteg(01);
    b11 = uj_beteg(11);
    b12 = uj_beteg(12);
    b13 = uj_beteg(13);
    b21 = uj_beteg(21);
    bx = uj_beteg(999);

    gocpont g = uj_gocpont(b0);

    uj_beteg_fertozes(g, b0, b11);
    uj_beteg_fertozes(g, b0, b12);
    uj_beteg_fertozes(g, b0, b13);

    g->beteg->fertozottek[0]->fertozottek = malloc(sizeof(beteg));
    g->beteg->fertozottek[0]->fertozottek[0] = b21;
    g->beteg->fertozottek[0]->fertozottek_szama = 1;

    kiir_gocpont(g);

    printf("Fertozott-e #%3d: %s \n", b21->id, fertozott_e(g, b21) ? "igen" : "nem" );
    printf("Fertozott-e #%3d: %s \n",  bx->id, fertozott_e(g,  bx) ? "igen" : "nem" );

    return 0;
}

gocpont uj_gocpont(beteg nulladikbeteg)
{
    gocpont g = malloc(sizeof(gocpont) * 2);
    g->beteg = nulladikbeteg;

    return g;
}


beteg uj_beteg(int azonosito)
{
    beteg b = malloc(sizeof(*b));
    b->id = azonosito;
    b->fertozottek_szama = 0;
    return b;
}


void kiir(beteg beteg)
{
    if (beteg == NULL)
        return;

    printf("Sorszam: %3d Fertozottek szama: %d\n", beteg->id, beteg->fertozottek_szama);

    for (int i = 0; i < beteg->fertozottek_szama ; i++)
    {
        kiir(beteg->fertozottek[i]);
    }    
}

void kiir_gocpont(gocpont g)
{
    beteg beteg = g->beteg;
    kiir(beteg);
    printf("\n");
}



int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott)
{
    beteg keresett = g->beteg;

    while (keresett->id != fertozo->id)
    {
        beteg tmp = keresett;
        for (int i=0; i<keresett->fertozottek_szama || tmp->id != keresett->id; i++)
            tmp = keresett->fertozottek[i];
    }


    if (keresett->id == fertozo->id)
    {
        if (g->beteg->fertozottek_szama == 0)
        {
            g->beteg->fertozottek = malloc(sizeof(beteg));
            g->beteg->fertozottek[g->beteg->fertozottek_szama] = fertozott;
            g->beteg->fertozottek_szama++;
        }
        else
        {
            g->beteg->fertozottek = realloc(g->beteg->fertozottek, sizeof(beteg) * (g->beteg->fertozottek_szama+1));
            g->beteg->fertozottek[g->beteg->fertozottek_szama] = fertozott;
            g->beteg->fertozottek_szama++;
        }
    }
    else
    {
        //beteg keresett = g->beteg;
        //while (keresett->id != fertozo->id)
    }

    return 0;
}

beteg keres(beteg fertozo, beteg keresett) {
    if (fertozo->id == keresett->id)
        return fertozo;

    beteg megtalalt;
    for (int i = 0; i < fertozo->fertozottek_szama ; i++)
        if ( (megtalalt = keres(fertozo->fertozottek[i], keresett)) != NULL ) return megtalalt;

    return NULL;
}

int fertozott_e(gocpont g, beteg b)
{
    if (g->beteg->id == b->id)
        return 1;
    beteg betegek = g->beteg;
    if (keres(betegek, b) != NULL)
        return 1;

    return 0;
}
