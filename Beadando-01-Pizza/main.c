#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int hrMennyiseg = 0;


havirendeles uj_havirendeles(rendeles r);
rendeles uj_rendeles(int futar, int nap, pizza p);
pizza uj_pizza(int db, char fajta);

void havirendeles_torol(havirendeles h);
void rendeles_torol(rendeles r);
void pizza_torol(pizza p);

char napi_max(havirendeles h, int nap); // 4
int napi_ossz(havirendeles h, int nap); // 5
void kiir(havirendeles h); // 6
int havi_min_nap(havirendeles h); // 7
char havi_max_pizza(havirendeles h); // 8
void plusz_rendeles(havirendeles h, rendeles r); // 9
void plusz_pizza(rendeles r, pizza p); // 10

void randomRendelesek(havirendeles h, rendeles r, pizza p, int n);

int main()
{
    pizza p;
    rendeles r;
    havirendeles h;

    p = uj_pizza(1, 'A');
    r = uj_rendeles(1, 1, p);
    h = uj_havirendeles(r);

    //kiir(h);

    p = uj_pizza(2, 'B');
    r = uj_rendeles(2, 2, p);
    plusz_rendeles(h, r);

    p = uj_pizza(3, 'C');
    r = uj_rendeles(3, 3, p);
    plusz_rendeles(h, r);

    p = uj_pizza(4, 'D');
    r = uj_rendeles(3, 3, p);
    p = uj_pizza(5, 'E');
    plusz_pizza(r,p);
    p = uj_pizza(3, 'F');
    plusz_pizza(r,p);

    p = uj_pizza(1, 'F');
    plusz_pizza(r,p);

    plusz_rendeles(h, r);

    //kiir(h);

    //printf("3. napi max pizza tipus: %c\n", napi_max(h,3));

    //randomRendelesek(h,r,p,10);



    srand(time(NULL));
    for (int i=h->mennyiseg; i<10; i++)
    {
        p = uj_pizza( rand() % 8 + 1, 'A' + (rand() % 6) );
        r = uj_rendeles( rand() % 8 + 1, rand() % 29 + 1, p );

        for (int j=0; j< rand() % 6; j++)
        {
            p = uj_pizza( rand() % 8 + 1, 'A' + (rand() % 6) );
            plusz_pizza(r,p);
        }

        plusz_rendeles(h,r);
    }


    kiir(h);

    pizza_torol(p);
    rendeles_torol(r);
    havirendeles_torol(h);

    return 0;
}

void randomRendelesek(havirendeles h, rendeles r, pizza p, int n)
{
    for (int i=h->mennyiseg; i<n; i++)
    {
        p = uj_pizza( rand() % 9, 'A' + (rand() % 6) );
        r = uj_rendeles( rand() % 9, rand() % 30, p );
        plusz_rendeles(h,r);
    }
}


pizza uj_pizza(int db, char fajta)
{
    if (db > 0 && db <= 9 && fajta >= 'A' && fajta <= 'F')
    {
        pizza p = malloc(sizeof (p));
        p->db = db;
        p->fajta = fajta;
        return p;
    }
    else
        return NULL;
}

void pizza_torol(pizza p)
{
    if (p->fajta != '\0')
    {
        free(p);
        p = NULL;
    }
}


rendeles uj_rendeles(int futar, int nap, pizza p)
{
    if (futar >= 1 && futar <= 9 && nap >= 1 && nap <= 30)
    {
        rendeles r = malloc(sizeof (r));
        r->pizza = malloc(sizeof (p) * 6);

        r->futar = futar;
        r->nap = nap;

        r->pizza[p->fajta - 'A'] = *p;

        return r;
    }
    else
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
    havirendeles h = malloc(sizeof(havirendeles));
    h->rendeles = malloc(sizeof(rendeles));

    h->rendeles[hrMennyiseg++] = r;
    h->mennyiseg++;

    return h;
}

void havirendeles_torol(havirendeles h)
{
    if (h != NULL)
    {
        free(h);
        h = NULL;
    }
}


void kiir(havirendeles h)
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

void plusz_rendeles(havirendeles h, rendeles r) // 9
{
    if (h->mennyiseg < 1000)
    {
        TRY
        {
            havirendeles temp = NULL;
            //h = (havirendeles ) realloc(h, sizeof(havirendeles) * (hrMennyiseg));
            //temp = (havirendeles ) realloc(h, sizeof(havirendeles) * (hrMennyiseg)); // h-t nem irom felul, ha nem sikerul lefoglalni a memoriat
            //temp = (havirendeles ) realloc(h, sizeof(h) + sizeof(h->rendeles[0]) * 2 );
            temp = (havirendeles ) realloc(h, sizeof(h) + sizeof(r) * 2 );

            if (temp == NULL)
            {
                printf("Hiba a memoria lefoglalasanal a plusz rendelesnek!");
                exit(1);
            }
            else
                h = temp;

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
    if (r->pizza[p->fajta - 'A'].db + p->db <= 9)
    {
        r->pizza[p->fajta - 'A'].db += p->db;
        r->pizza[p->fajta - 'A'].fajta = p->fajta;
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

        max = 0;
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
