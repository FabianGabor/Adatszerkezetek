/*
 * Fábián Gábor
 * CXNU8T
 * https://github.com/FabianGabor/Adatszerkezetek/tree/master/Beadando-02-Gocpont
 */

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
int megfertozte_e(gocpont g, beteg b1, beteg b2);                   //  9. OK
int fertozobb_e(gocpont g, beteg b1, beteg b2);                     // 10. OK

// segedfuggvenyek:
beteg keres(beteg fertozo, beteg keresett);
beteg keres_szulo(beteg fertozo, beteg keresett);
void kiir(beteg beteg);
//int sum(beteg beteg);
int fertozottek_szama_rekurziv(gocpont g, beteg b);
void beteg_torol_helyesen_void(beteg *b);
void beteg_torol_gocpontbol(gocpont g, beteg b);
void beteg_torol_rekurziv(beteg beteg);                              // betegek torlese rekurzivan, meghivja a void beteg_torol(beteg b) eljarast
void kiir_gocpont_fa(gocpont g);
void print_structure ( beteg beteg, int szint, int irany );
int szamol_rekurziv(beteg b);

int main()
{
    // 2. Uj beteg letrehozasa azonositoval    
    beteg b01 = uj_beteg(01);
    beteg b11 = uj_beteg(11);
    beteg b12 = uj_beteg(12);
    beteg b13 = uj_beteg(13);
    beteg b111 = uj_beteg(111); // 11. beteg 1. fertozottje = 11+1 = 111
    beteg b112 = uj_beteg(112); // 11. beteg 2. fertozottje = 11+2 = 112
    beteg b113 = uj_beteg(113); // 11. beteg 3. fertozottje = 11+3 = 113
    beteg b131 = uj_beteg(131); // 13. beteg 1. fertozottje = 13+1 = 131
    beteg b132 = uj_beteg(132); // 13. beteg 2. fertozottje = 13+2 = 132
    beteg b1321 = uj_beteg(1321); // 131. beteg 1. fertozottje = 132+1 = 1321
    beteg b13211 = uj_beteg(13211); // 1311. beteg 1. fertozottje
    beteg b13212 = uj_beteg(13212); // 1311. beteg 2. fertozottje
    beteg b13213 = uj_beteg(13213); // 1311. beteg 3. fertozottje
    beteg b13214 = uj_beteg(13214); // 1311. beteg 4. fertozottje

    // 2. Uj gocpont
    gocpont g = uj_gocpont(b01);

    // 6.
    uj_beteg_fertozes(g, b01, b11);
    uj_beteg_fertozes(g, b01, b12);
    uj_beteg_fertozes(g, b01, b13);
    uj_beteg_fertozes(g, b11, b111);
    uj_beteg_fertozes(g, b11, b112);
    uj_beteg_fertozes(g, b11, b113);
    uj_beteg_fertozes(g, b13, b131);
    uj_beteg_fertozes(g, b13, b132);
    uj_beteg_fertozes(g, b132, b1321);
    uj_beteg_fertozes(g, b1321, b13211);
    uj_beteg_fertozes(g, b1321, b13212);
    uj_beteg_fertozes(g, b1321, b13213);
    uj_beteg_fertozes(g, b1321, b13214);

    // 7.
    kiir_gocpont(g);    
    kiir_gocpont_fa(g);   // fa reprezentacio

    // 4.
    printf(" 4. Letszam g-ben: %d\n\n", letszam(g));

    // 5.
    printf(" 5. b0  altal megfertozottek szama: %d\n", fertozottek_szama(g, b01));
    printf(" 5. b11 altal megfertozottek szama: %d\n", fertozottek_szama(g, b11));
    printf(" 5. b12 altal megfertozottek szama: %d\n", fertozottek_szama(g, b12));
    printf(" 5. b13 altal megfertozottek szama: %d\n\n", fertozottek_szama(g, b13));

    // 8.
    printf(" 8. Fertozott-e g-ben #%d? %s \n", b112->id, fertozott_e(g, b112) ? "igen" : "nem" );

    // 9.
    printf(" 9. Megfertozte-e g-ben #%d beteg #%d beteget? %s \n", b11->id, b113->id, megfertozte_e(g, b11, b113) ? "igen" : "nem" );
    printf(" 9. Megfertozte-e g-ben #%d beteg #%d beteget? %s \n", b11->id, b131->id, megfertozte_e(g, b11, b131) ? "igen" : "nem" );

    // 10. Fertozobb-e?
    beteg beteg1 = b11;
    beteg beteg2 = b13;

    printf("10. Fertozobb-e g-ben #%d beteg #%d betegnel? ", beteg1->id, beteg2->id);
    switch (fertozobb_e(g, beteg1, beteg2))
    {
        case (1):
            printf("igen\n");
            break;
        case (0):
            printf("egyforma\n");
            break;
        case (-1):
            printf("nem\n");
            break;
    };
    printf("\n");


    kiir_gocpont_fa(g);
    printf("Letszam g-ben: %d\n\n", letszam(g));

    printf("%d torlese, gocpontbol is:\n", b11->id);
    //beteg_torol(b11);                 // Hasznalata nem ajanlott ilyen formaban, mert a gocpontban nem tudja megszunteti a hivatkozast ra. Last: beteg_torol_helyesen_void fuggvenyt
    //beteg_torol_rekurziv(b11);        // a beteg_torol()-t hivja rekurzivan. Hasznalata nem ajanlott ilyen formaban, mert a gocpontban nem tudja megszunteti a hivatkozast ra.
    //b11 = NULL;                       // beteg_torol() es beteg_torol_rekurziv() eseten kell a NULL, kulonben a gocpontban nem lesz NULL erteku, hanem 'logo' pointer, memoriaszemet marad. Specifikacioban a torles 'beteg' tipusu kellett volna legyen, hogy onnan vissza lehessen teriteni az erteket, esetleg beteg_torol(gocpont *g)    
    //beteg_torol_helyesen_void(&b11);  // ez mar legalabb NULL-ra tudja allitani a beteget
    beteg_torol_gocpontbol(g, b11);     // ez jol torol, a gocpontban a torolt beteg leszarmazottjait is torli, minden torolt elemet felszabadit es NULL-ra allit, illetve az adatszerkezetben 1-gyel eltolja a tovabbi betegeket, a memoriat pedig ujrameretezi realloc fuggvennyel

    kiir_gocpont_fa(g);
    printf("Letszam g-ben: %d\n\n", letszam(g));

    // 3. Gocpont torlese, benne betegek torlese
    printf("3. gocpont_torol(g) \n");
    gocpont_torol(g);
    g = NULL;                           // ajanlott, hogy a gocpont ne legyen memoriaszemet

    printf("7. kiir_gocpont(g) \n");
    kiir_gocpont(g);
    kiir_gocpont_fa(g);

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

// 3.
void gocpont_torol(gocpont g)
{
    beteg_torol_rekurziv(g->beteg); // betegek torlese rekurzivan
    //g->beteg->fertozottek_szama = 0;
    free(g);
    g = NULL; // ez jo lenne, de nem lehetseges itt
}

void beteg_torol(beteg b)
{
    if (b != NULL)
        free(b);
    b = NULL; // igy ezt nem tudja atadni
}

// 4.
int letszam(gocpont g)
{
    int szamol = 0;
    if (g->beteg!= NULL) {
        szamol = szamol_rekurziv(g->beteg);
    }
    return szamol;
}

// 5.
int fertozottek_szama(gocpont g, beteg b)
{
    beteg beteg = b;
    if (keres(g->beteg, b) != NULL)
    {
        return beteg->fertozottek_szama;
    }
    return -1;
}

// 6.
int uj_beteg_fertozes(gocpont g, beteg fertozo, beteg fertozott)
{
    beteg keresett = keres(g->beteg, fertozo);

    if (keresett != NULL)
    {
        if (keresett->fertozottek_szama == 0)
            keresett->fertozottek = malloc(sizeof (beteg));
        else
            keresett->fertozottek = realloc(keresett->fertozottek, sizeof (beteg) * (keresett->fertozottek_szama+1));

        if (!keresett->fertozottek) // nem sikerul a memoria foglalas
        {
            keresett->fertozottek = NULL;
            exit(1);
        }

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
        kiir(g->beteg);
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

// 10.
int fertozobb_e(gocpont g, beteg b1, beteg b2)
{
    if (fertozottek_szama(g,b1) > fertozottek_szama(g,b2)) return 1;
    if (fertozottek_szama(g,b1) == fertozottek_szama(g,b2)) return 0;
    return -1;
}




/****************************************************
****************** SEGEDFUGGVENYEK ******************
****************************************************/

void kiir(beteg beteg)
{
    if (beteg == NULL)
        return;

    printf("Sorszam: %6d Fertozottek szama: %d\n", beteg->id, beteg->fertozottek_szama);

    for (int i = 0; i < beteg->fertozottek_szama ; i++)
    {
        kiir(beteg->fertozottek[i]);
    }
}


beteg keres(beteg fertozo, beteg keresett)
{
    if (fertozo->id == keresett->id)
        return fertozo;

    beteg megtalalt;
    for (int i = 0; i < fertozo->fertozottek_szama ; i++)
        if ( (megtalalt = keres(fertozo->fertozottek[i], keresett)) != NULL ) return megtalalt;

    return NULL;
}

beteg keres_szulo(beteg fertozo, beteg keresett)
{
    if (fertozo->id == keresett->id)
        return fertozo;

    for (int i = 0; i < fertozo->fertozottek_szama ; i++)
    {
        if (fertozo->fertozottek[i]->id == keresett->id)
            return fertozo;
        else
            keres(fertozo->fertozottek[i], keresett);
    }


    return NULL;
}





int szamol_rekurziv(beteg b)
{
    int szamol = 1;
    for (int i = 0; i < b->fertozottek_szama; i++)
    {
        szamol += szamol_rekurziv(b->fertozottek[i]);
    }

    return szamol;
}


int fertozottek_szama_rekurziv(gocpont g, beteg b)
{
    beteg beteg = b;
    if (keres(g->beteg, b) != NULL)
        return szamol_rekurziv(beteg) + 1; // a beteget nem kell szamolni;

    return -1;
}

void beteg_torol_helyesen_void(beteg *b)
{
    free(*b);
    *b = NULL;
}

void beteg_torol_gocpontbol(gocpont g, beteg b)
{
    beteg szulo = keres_szulo(g->beteg, b); // a torolni kivant beteg szuloje / fertozoje
    if (szulo == NULL)
        return;

    int i=0;
    while (szulo->fertozottek[i]->id != b->id && i < szulo->fertozottek_szama)
    {
        i++;
    }

    for ( ; i < szulo->fertozottek_szama-1; i++)
        szulo->fertozottek[i] = szulo->fertozottek[i+1];

    szulo->fertozottek_szama--;
    szulo->fertozottek = realloc(szulo->fertozottek, sizeof (beteg) * (szulo->fertozottek_szama));

    beteg_torol_rekurziv(b);
}


void beteg_torol_rekurziv(beteg beteg)
{
    if (beteg == NULL)
        return;

    for (int i = 0; i < beteg->fertozottek_szama ; i++)
    {
        beteg_torol_rekurziv(beteg->fertozottek[i]);
    }
    beteg_torol(beteg); // egy beteg torlese
    beteg = NULL;
}




void kiir_gocpont_fa(gocpont g)
{
    if (g != NULL)
        print_structure(g->beteg, 0, 0);
    printf("\n");
}



void print_structure ( beteg beteg, int szint, int irany )
{
    if ( beteg == NULL ) {
        for ( int i = 0; i < szint; i++ )
            putchar ( '\t' );
        puts ( "~" );
    }
    if (beteg->id == 0)
        printf("\n");
    else
    {
        for (int i = beteg->fertozottek_szama - 1; i > beteg->fertozottek_szama / 2 - 1; i--)
        {
            print_structure(beteg->fertozottek[i], szint+1, 1);
        }
        //printf("\n");

        for ( int i = 0; i < szint; i++ )
            printf("\t");

        if (szint)
        {
            if (irany)
                printf("_/");
            else
                printf("‾\\");
        }


        printf ( "%3d \n", beteg->id );


        for (int i = 0; i < beteg->fertozottek_szama / 2; i++)
        {
            print_structure(beteg->fertozottek[i], szint+1, 0);
        }
        //printf("\n");
    }
}
