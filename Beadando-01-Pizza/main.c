#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)

typedef struct pizza {
    char fajta;
    int db;
} *pizza;

typedef struct rendeles {
    int futar;
    int nap;
    pizza pizza;
} *rendeles;

typedef struct havirendeles {
    rendeles *rendeles; // * 1000
    int mennyiseg;
} *havirendeles;


typedef struct futar {
    int pizzaTipusokSzama;
    int futar;
    pizza pizza;
} *futar;

typedef struct nap {
    int napSorszam;
    int futarokSzama;
    futar *futarok;
} *nap;

typedef struct napok {
    int napokSzama;
    nap *nap;
} napok;

//int hrMennyiseg = 0;


havirendeles uj_havirendeles(rendeles r);
rendeles uj_rendeles(int futar, int nap, pizza p);
pizza uj_pizza(int db, char fajta);

void havirendeles_torol(havirendeles h);
void rendeles_torol(rendeles r);
void pizza_torol(pizza p);

char napi_max(havirendeles h, int nap); // 4
int napi_ossz(havirendeles h, int nap); // 5
void kiir(havirendeles h); // 6
void kiir_havirendelesek(havirendeles h); // 6
int havi_min_nap(havirendeles h); // 7
char havi_max_pizza(havirendeles h); // 8
void plusz_rendeles(havirendeles h, rendeles r); // 9
void plusz_pizza(rendeles r, pizza p); // 10

void randomRendelesek(havirendeles h, rendeles r, pizza p, int n);
int benneNap (nap nap, int napokSzama, int keresettNap);

int main()
{
    pizza p;
    rendeles r;
    havirendeles h;

    //kiir(h);

    p = uj_pizza(1, 'A');
    r = uj_rendeles(1, 1, p);
    h = uj_havirendeles(r);

    //kiir(h);

    p = uj_pizza(2, 'B');
    r = uj_rendeles(1, 2, p);
    plusz_rendeles(h, r);

    p = uj_pizza(5, 'C');
    r = uj_rendeles(1, 2, p);
    plusz_rendeles(h, r);

    p = uj_pizza(3, 'B');
    r = uj_rendeles(2, 3, p);
    plusz_rendeles(h, r);


    p = uj_pizza(0, 'G');
    r = uj_rendeles(2, 2, p);
    p = uj_pizza(0, 'G');
    plusz_pizza(r,p);
    plusz_rendeles(h, r);

    p = uj_pizza(0, 'A');
    r = uj_rendeles(2, 2, p);
    p = uj_pizza(1, 'A');
    plusz_pizza(r,p);
    plusz_rendeles(h, r);


    randomRendelesek(h,r,p,3);

    kiir_havirendelesek(h);
    kiir(h);

    int nap = 2;
    printf("%d. napi max pizza tipus: %c\n", nap, napi_max(h,nap));
    printf("%d. napi kiszallitott pizzak szama: %d\n", nap, napi_ossz(h, nap));

    printf("A hónap leggyengébb forgalmú napja: %d \n", havi_min_nap(h));
    printf("A honap legkelendobb pizzaja: %c\n", havi_max_pizza(h));

    pizza_torol(p);
    rendeles_torol(r);
    havirendeles_torol(h);

    return 0;
}

void randomRendelesek(havirendeles h, rendeles r, pizza p, int n)
{
    srand(time(NULL));
    for (int i=h->mennyiseg; i<n; i++)
    {
        p = uj_pizza( rand() % 9 + 1, 'A' + rand() % 6);
        r = uj_rendeles( rand() % 8 + 1, rand() % 30 + 1, p );

        for (int j=0; j< rand() % 6; j++)
        {
            p = uj_pizza( rand() % 8 + 1, 'A' + rand() % 6 ); // i=8 eseten db = i%8=0, ami miatt uj_pizza = NULL
            plusz_pizza(r,p);
        }

        plusz_rendeles(h,r);
    }
}


pizza uj_pizza(int db, char fajta)
{
    if (db > 0 && db <= 9 && fajta >= 'A' && fajta <= 'F')
    {
        //pizza p = malloc(sizeof (p));
        pizza p = malloc(sizeof (*p));

        p->db = db;
        p->fajta = fajta;
        return p;
    }
    else
        return NULL;
}

void pizza_torol(pizza p)
{
    if (!p || p->fajta != '\0')
    {
        free(p);
        //p = NULL;
    }
}


rendeles uj_rendeles(int futar, int nap, pizza p)
{
    if (p) // p NULL check
    {
        if (futar >= 1 && futar <= 9 && nap >= 1 && nap <= 30)
        {
            //rendeles r = calloc(1,sizeof(*r));
            rendeles r = malloc(sizeof(*r));
            r->pizza = calloc(6,sizeof(*p)); // el kene donteni, hogy memoriat vagy futasidot szeretnenk sporolni.

            r->futar = futar;
            r->nap = nap;

            r->pizza[p->fajta - 'A'] = *p;

            return r;
        }
        else
            return NULL;
    }
    return NULL;
}

void rendeles_torol(rendeles r)
{
    if (r != NULL)
    {
        free(r->pizza);
        r->pizza = NULL;
        free (r);
        r = NULL;
    }
}


havirendeles uj_havirendeles(rendeles r)
{
    if (r) // r NULL check
    {        
        havirendeles h = malloc(sizeof(*h));
        h->rendeles = malloc(sizeof(*r));

        h->mennyiseg = 0;
        h->rendeles[h->mennyiseg++] = r;

        return h;
    }
    return NULL;
}

void havirendeles_torol(havirendeles h)
{
    if (h != NULL)
    {
        for (int i=0; i<h->mennyiseg; i++)
        {
            rendeles_torol(h->rendeles[i]);
        }
        free(h);
        h = NULL;
    }
}


void kiir_havirendelesek(havirendeles h)
{
    for (int i=0; i< h->mennyiseg; i++) {
        printf("Rendeles: %d.\n", i+1);
        printf("\tNap: %d \n", h->rendeles[i]->nap);
        printf("\tFutar: %d \n", h->rendeles[i]->futar);

        for (int j=0; j < 6; j++)
            if (h->rendeles[i]->pizza[j].db > 0)
                printf("\t\tPizza: %d %c \n", h->rendeles[i]->pizza[j].db, h->rendeles[i]->pizza[j].fajta);
    }
    printf("\n");
}

void kiir(havirendeles h) // 6
{
    typedef int rendeles;
    typedef struct futar {
        rendeles rendelesek[6];
        int van;
    } futar;

    typedef struct nap {
        futar futar[9];
        int van;
    } nap;

    nap napok[30] =  {0};

    for (int i=0; i< h->mennyiseg; i++)
    {
        for (int j=0; j<6; j++)
            if (h->rendeles[i]->pizza[j].db)
            {
                napok[h->rendeles[i]->nap - 1].futar[h->rendeles[i]->futar - 1].rendelesek[j] += h->rendeles[i]->pizza[j].db;
                napok[h->rendeles[i]->nap - 1].van++;
                napok[h->rendeles[i]->nap - 1].futar[h->rendeles[i]->futar - 1].van++;
            }
    }

    for (int i=0; i<30; i++)
    {
        if (napok[i].van)
        {
            printf("%d. nap\n", i+1);
            for (int j=0; j<9; j++)
            {
                if (napok[i].futar[j].van)
                {
                    printf("\t%d. futar: ", j+1);
                    for (int k=0; k<6; k++)
                        if (napok[i].futar[j].rendelesek[k])
                            printf("%c=%d ", 'A'+k, napok[i].futar[j].rendelesek[k]);
                    printf("\n");
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}


void plusz_rendeles(havirendeles h, rendeles r) // 9
{
    if (h->mennyiseg < 1000 && r)
    {
        TRY
        {
            rendeles *temp = NULL;
            //temp = (rendeles *) realloc(h->rendeles, sizeof(r) * (h->mennyiseg + 1) );
            temp = (rendeles *) realloc(h->rendeles, sizeof(*r) * (h->mennyiseg + 1) );

            if (temp == NULL)
            {
                printf("Hiba a memoria lefoglalasanal a plusz rendelesnek!");
                exit(1);
            }
            else
                h->rendeles = temp;

            h->rendeles[h->mennyiseg++] = r;
            //THROW;
        }
        CATCH
        {
            printf("Got Exception!\n");
        }
        ETRY;
    }
}


void plusz_pizza(rendeles r, pizza p)  // 10
{
    if (p && r)
    {
        if (r->pizza[p->fajta - 'A'].db + p->db <= 9)
        {
            r->pizza[p->fajta - 'A'].db += p->db;
            r->pizza[p->fajta - 'A'].fajta = p->fajta;
        }
    }
}

char napi_max(havirendeles h, int nap) // 4
{
    if (nap > 0 && nap <= 30 && h->mennyiseg < 1001)
    {
        unsigned int count[6] = {0};
        int max = 0;

        for (int i=0; i< h->mennyiseg; i++)
            if (h->rendeles[i]->nap == nap)
                for (int j=0; j<6; j++)
                    count[ h->rendeles[i]->pizza[j].fajta - 'A' ] += h->rendeles[i]->pizza[j].db;

        for (int i=1; i<6; i++)
            if (count[i] > count[max])
                max = i;
        if (count[max] == 0)
            return 'X';

        for (int i=0; i<6; i++)
            if (count[i] == count[max] && i != max)
                return 'Y';

        return 'A' + max;
    }

    return 'X';
}

int napi_ossz(havirendeles h, int nap) // 5
{
    unsigned int count = 0;

    for (int i=0; i < h->mennyiseg; i++)
        if (h->rendeles[i]->nap == nap)
            for (int j=0; j<6; j++)
                count += h->rendeles[i]->pizza[j].db;
    return count;
}

int havi_min_nap(havirendeles h) // 7
{
    if (h->mennyiseg < 1001)
    {
        unsigned int count[30] = {0};
        int min = 0;

        for (int i=0; i< h->mennyiseg; i++)
            for (int j=0; j<6; j++)
                count[ h->rendeles[i]->nap - 1 ] += h->rendeles[i]->pizza[j].db;


        for (int i=1; i<30; i++)
            if (count[i] < count[min])
                min = i;


        for (int i=0; i<30; i++)
            if (count[i] == count[min] && i != min) // tobb minimum, es nem onmagaval egyenlo
                return -1;

        return (count[min] == 0) ? 0 : min + 1;
    }

    return 0;
}

char havi_max_pizza(havirendeles h) // 8
{
    if (h->mennyiseg < 1001)
    {
        unsigned int count[6] = {0};
        int max = 0;

        for (int i=0; i< h->mennyiseg; i++)
            for (int j=0; j<6; j++)
                count[ h->rendeles[i]->pizza[j].fajta - 'A' ] += h->rendeles[i]->pizza[j].db;

        for (int i=1; i<6; i++)
            if (count[i] > count[max])
                max = i;
        if (count[max] == 0)
            return 'X';

        for (int i=0; i<6; i++)
            if (count[i] == count[max] && i != max)
                return 'Y';

        return 'A' + max;
    }

    return 'X';
}
