#include <stdio.h>
#include <stdlib.h>

typedef unsigned int azonosito;

typedef struct beteg {
    azonosito id;
    struct beteg **fertozottek;
    int fertozottek_szama;
} *beteg;

typedef struct gocpont {
    beteg beteg;
} *gocpont;

gocpont uj_gocpont(beteg nulladikbeteg);                            //  2. OK
beteg uj_beteg(int azonosito);                                      //  2. OK

void gocpont_torol(gocpont g);                                      //  3.
void beteg_torol(beteg b);                                          //  3.

int letszam(gocpont g);                                             //  4. OK
int fertozottek_szama(gocpont g, beteg b);                          //  5.

int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott);   //  6. OK

void kiir_gocpont(gocpont g);                                       //  7. OK
int fertozott_e(gocpont g, beteg b);                                //  8. OK
int megfertozte_e(gocpont g, beteg b1, beteg b2);                   //  9.
int fertozobb_e(gocpont g, beteg b1, beteg b2);                     // 10.

// segedfuggvenyek:
beteg keres(beteg fertozo, beteg keresett);
void kiir(beteg beteg);
int sum(beteg beteg);


int main()
{
    beteg b0, b11, b12, b13, b21,bx;
    b0 = uj_beteg(01);
    b11 = uj_beteg(11);
    b12 = uj_beteg(12);
    b13 = uj_beteg(13);
    b21 = uj_beteg(21);
    bx = uj_beteg(999);

    gocpont g0 = uj_gocpont(b0);

    uj_beteg_fertozes(g0, b0, b11);
    uj_beteg_fertozes(g0, b0, b12);
    uj_beteg_fertozes(g0, b0, b13);
    uj_beteg_fertozes(g0, b11, b21);

    gocpont g1 = uj_gocpont(bx);
    uj_beteg_fertozes(g1, bx, b21);

    kiir_gocpont(g0);
    kiir_gocpont(g1);

    printf("Fertozott-e #%3d: %s \n", b21->id, fertozott_e(g0, b21) ? "igen" : "nem" );
    printf("Fertozott-e #%3d: %s \n",  bx->id, fertozott_e(g0,  bx) ? "igen" : "nem" );

    letszam(g0);
    letszam(g1);

    return 0;
}

// 2.
gocpont uj_gocpont(beteg nulladikbeteg)
{
    gocpont g = malloc(sizeof(*g));
    g->beteg = nulladikbeteg;

    return g;
}

// 2.
beteg uj_beteg(int azonosito)
{
    beteg b = malloc(sizeof(*b));
    b->id = azonosito;
    b->fertozottek_szama = 0;
    return b;
}

// 4.
int letszam(gocpont g)
{
    beteg beteg = g->beteg;
    int summ = sum(beteg) + 1; // + elso beteg
    printf("Letszam: %d\n", summ);
    return summ;
}

// 6.
int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott)
{
    beteg keresett = g->beteg;
    keresett = keres(keresett, fertozo);

    if (keresett != NULL)
    {
        if (keresett->fertozottek_szama == 0)
            keresett->fertozottek = malloc(sizeof (beteg));
        else
            keresett->fertozottek = realloc(keresett->fertozottek, sizeof (beteg) * (keresett->fertozottek_szama+1));

        keresett->fertozottek[keresett->fertozottek_szama] = fertozott;
        keresett->fertozottek_szama++;

        return 1;
    }
    return 0;
}

// 7.
void kiir_gocpont(gocpont g)
{
    beteg beteg = g->beteg;
    kiir(beteg);
    printf("\n");
}

// 8.
int fertozott_e(gocpont g, beteg b)
{
    if (g->beteg->id == b->id)
        return 1;
    beteg betegek = g->beteg;
    if (keres(betegek, b) != NULL)
        return 1;

    return 0;
}




/****************************************************
****************** SEGEDFUGGVENYEK ******************
****************************************************/

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


beteg keres(beteg fertozo, beteg keresett) {
    if (fertozo->id == keresett->id)
        return fertozo;

    beteg megtalalt;
    for (int i = 0; i < fertozo->fertozottek_szama ; i++)
        if ( (megtalalt = keres(fertozo->fertozottek[i], keresett)) != NULL ) return megtalalt;

    return NULL;
}



int sum(beteg beteg)
{
    if (beteg == NULL)
        return 0;
    if (beteg->fertozottek == NULL)
        return 0;

    for (int i = 0; i < beteg->fertozottek_szama; i++)
        return sum(beteg->fertozottek[i]) + beteg->fertozottek_szama;

    return 0;
}
