#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
    //int mennyiseg;
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

/*
int havirendeles_mennyiseg (havirendeles r)
{
    return r.mennyiseg;
}
*/

int main()
{
    pizza p;
    rendeles r;
    havirendeles h;

    p = uj_pizza(1, 'A');
    r = uj_rendeles(1, 1, p);
    h = uj_havirendeles(r);

    kiir(h);

    p = uj_pizza(2, 'B');
    r = uj_rendeles(2, 2, p);
    plusz_rendeles(h, r);

    p = uj_pizza(3, 'C');
    r = uj_rendeles(3, 3, p);
    plusz_rendeles(h, r);

    p = uj_pizza(4, 'D');
    r = uj_rendeles(3, 3, p);
    p = uj_pizza(5, 'E');
    r = uj_rendeles(3, 3, p);
    plusz_rendeles(h, r);

    kiir(h);

    /*
    *p = uj_pizza(9, 'B');
    *r = uj_rendeles(2, 8, *p);

    plusz_rendeles(*hr, *r);

    //kiir(*hr);

    *p = uj_pizza(66, 'C');
    *r = uj_rendeles(3, 3, *p);

    plusz_rendeles(*hr, *r);



    //printf("%c %d\n", p->fajta, p->db);
    kiir(*hr);
    //printf("Rendeles mennyisege: %d\n", hr->mennyiseg);

    free(p);
    free(r);

    */
    pizza_torol(p);
    rendeles_torol(r);
    havirendeles_torol(h);

    return 0;
}


pizza uj_pizza(int db, char fajta) {
    pizza p = malloc(sizeof (pizza));
    p->db = db;
    p->fajta = fajta;

    return p;
}

void pizza_torol(pizza p) {
    free(p);
}


rendeles uj_rendeles(int futar, int nap, pizza p) {
    rendeles r = malloc(sizeof (rendeles));
    r->pizza = malloc(sizeof (pizza) * 6);

    r->futar = futar;
    r->nap = nap;

    r->pizza[p->fajta - 'A'] = *p;

    return r;
}

void rendeles_torol(rendeles r) {
    free (r);
}


havirendeles uj_havirendeles(rendeles r) {
    havirendeles h = malloc(sizeof(havirendeles));
    h->rendeles = malloc(sizeof(rendeles));

    h->rendeles[hrMennyiseg++] = r;

    return h;
}

void havirendeles_torol(havirendeles h) {
    free(h);
}


void kiir(havirendeles h) {
    //h.mennyiseg = sizeof (*h.rendeles) / sizeof(h.rendeles);
    printf("Havirendeles mennyiseg: %d\n", hrMennyiseg);

    for (int i=0; i<hrMennyiseg; i++) {
        printf("Rendeles: %d.\n", i+1);
        printf("\tNap: %d \n", h->rendeles[i]->nap);
        printf("\tFutar: %d \n", h->rendeles[i]->futar);

        //int rendeles_mennyiseg = (int) (sizeof(*h.rendeles[0].pizza) );
        //printf("\tsizeof(rendeles_mennyiseg): %d\n", rendeles_mennyiseg);

        for (int j=0; j < 6; j++)
            //if (h->rendeles[i]->pizza[j]->db > 0)
            if (h->rendeles[i]->pizza[j].db > 0)
                printf("\t\tPizza: %d %c \n", h->rendeles[i]->pizza[j].db, h->rendeles[i]->pizza[j].fajta);
    }
    printf("\n");
}

void plusz_rendeles(havirendeles h, rendeles r) // 9
{

    havirendeles temp = NULL;
    //h = (havirendeles ) realloc(h, sizeof(havirendeles) * (hrMennyiseg));
    temp = (havirendeles ) realloc(h, sizeof(havirendeles) * (hrMennyiseg)); // h-t nem irom felul, ha nem sikerul lefoglalni a memoriat

    if (temp == NULL)
    {
        printf("Hiba a memoria lefoglalasanal");
        exit(1);
    }
    else
    {
        h = temp;
    }

    h->rendeles[hrMennyiseg++] = r;
}
