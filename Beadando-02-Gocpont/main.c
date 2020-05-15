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

void gocpont_torol(gocpont g);                                      //  3. OK
void beteg_torol(beteg b);                                          //  3. OK

int letszam(gocpont g);                                             //  4. OK
int fertozottek_szama(gocpont g, beteg b);                          //  5. OK

int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott);   //  6. OK

void kiir_gocpont(gocpont g);                                       //  7. OK
int fertozott_e(gocpont g, beteg b);                                //  8. OK
int megfertozte_e(gocpont g, beteg b1, beteg b2);                   //  9.
int fertozobb_e(gocpont g, beteg b1, beteg b2);                     // 10.

// segedfuggvenyek:
beteg keres(beteg fertozo, beteg keresett);
void kiir(beteg beteg);
int sum(beteg beteg);
void gocpont_beteg_torol(beteg beteg);
void PrintTree(gocpont g);
void print_structure ( beteg beteg, int level, int irany );


int main()
{
    beteg b0, b11, b12, b13, b21, b22, bx, by;
    b0 = uj_beteg(01);
    b11 = uj_beteg(11);
    b12 = uj_beteg(12);
    b13 = uj_beteg(13);
    b21 = uj_beteg(21);
    b22 = uj_beteg(22);
    bx = uj_beteg(98);
    by = uj_beteg(99);

    gocpont g0 = uj_gocpont(b0);

    uj_beteg_fertozes(g0, b0, b11);
    uj_beteg_fertozes(g0, b0, b12);
    uj_beteg_fertozes(g0, b0, b13);
    uj_beteg_fertozes(g0, b11, b21);
    uj_beteg_fertozes(g0, b11, b22);
    uj_beteg_fertozes(g0, b13, bx);
    //uj_beteg_fertozes(g0, b13, by);

    gocpont g1 = uj_gocpont(by);
    uj_beteg_fertozes(g1, by, b21);

    kiir_gocpont(g0);
    PrintTree(g0);

    kiir_gocpont(g1);
    PrintTree(g1);

    printf("Fertozott-e g0-ban #%d? %s \n", b21->id, fertozott_e(g0, b21) ? "igen" : "nem" );
    printf("Fertozott-e g1-ben #%d? %s \n",  bx->id, fertozott_e(g1,  bx) ? "igen" : "nem" );

    letszam(g0);
    letszam(g1);

    fertozottek_szama(g0, b13);

    printf("Megfertozte-e g0-ban #%d beteg #%d beteget? %s \n", b11->id, b22->id, megfertozte_e(g0, b11, b22) ? "igen" : "nem" );
    printf("Megfertozte-e g0-ban #%d beteg #%d beteget? %s \n", b11->id, b13->id, megfertozte_e(g0, b11, b13) ? "igen" : "nem" );


    gocpont_torol(g0);

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

void gocpont_torol(gocpont g)
{
    beteg beteg = g->beteg;
    gocpont_beteg_torol(beteg);
    g->beteg->fertozottek_szama = 0;
    free(g);
    g = NULL;
}

void beteg_torol(beteg b)
{
    free(b);
}

// 4.
int letszam(gocpont g)
{
    beteg beteg = g->beteg;
    int summ = sum(beteg);
    printf("Letszam: %d\n", summ);
    return summ;
}

int fertozottek_szama(gocpont g, beteg b)
{
    beteg beteg = b;
    if (keres(g->beteg, b) != NULL)
    {
        int summ = sum(beteg) - 1; // a beteget nem kell szamolni
        printf("Fertozottek szama: %d\n", summ);
        return summ;
    }
    return -1;
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
    if (g != NULL)
    {
        beteg beteg = g->beteg;
        kiir(beteg);
        printf("\n");
    }
    else
        printf("Nem letezo gocpont! \n");
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

// 9.
int megfertozte_e(gocpont g, beteg b1, beteg b2)
{
    beteg keresett1;
    if ((keresett1 = keres(g->beteg, b1)) != NULL)
    {
        for (int i=0; i<keresett1->fertozottek_szama; i++)
            if (keresett1->fertozottek[i]->id == b2->id)
                return 1;
    }

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
        return sum(beteg->fertozottek[i]) + beteg->fertozottek_szama + 1; // +1 fertozo

    return 0;
}


void gocpont_beteg_torol(beteg beteg)
{
    if (beteg == NULL)
        return;

    for (int i = 0; i < beteg->fertozottek_szama ; i++)
    {
        gocpont_beteg_torol(beteg->fertozottek[i]);
    }
    beteg_torol(beteg);
}




void PrintTree(gocpont g)
{
    print_structure(g->beteg, 0, 0);
}



void print_structure ( beteg beteg, int level, int irany )
{
    if ( beteg == NULL ) {
        for ( int i = 0; i < level; i++ )
            putchar ( '\t' );
        puts ( "~" );
    }
    if (beteg->id == 0)
        printf("\n");
    else
    {
        for (int i = beteg->fertozottek_szama - 1; i > beteg->fertozottek_szama / 2 - 1; i--)
        {
            print_structure(beteg->fertozottek[i], level+1, 1);
        }
        //printf("\n");

        for ( int i = 0; i < level; i++ )
            printf("\t");

        if (level)
        {
            if (irany)
                printf("_/");
            else
                printf("‾\\");
        }


        printf ( "%3d \n", beteg->id );


        for (int i = 0; i < beteg->fertozottek_szama / 2; i++)
        {
            print_structure(beteg->fertozottek[i], level+1, 0);
        }
        //printf("\n");
    }
}
