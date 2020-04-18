#include <stdio.h>
#include <stdlib.h>

typedef struct pizza {
    char fajta;
    int db;
} pizza;

typedef struct rendeles {
    int futar;
    int nap;
    pizza *pizza;
} rendeles;

typedef struct havirendeles {
    rendeles *rendeles; // * 1000
    int mennyiseg;
} havirendeles;


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


int havirendeles_mennyiseg (havirendeles r)
{
    return r.mennyiseg;
}

int main()
{    
    pizza *p = malloc(sizeof (pizza));
    rendeles *r = malloc(sizeof (rendeles));
    r->pizza = malloc(sizeof (pizza) * 6);


    havirendeles *hr = malloc(sizeof (havirendeles) );
    hr->mennyiseg = 0;

    *p = uj_pizza(8, 'B');
    printf("%c %d\n", p->fajta, p->db);

    *r = uj_rendeles(4, 16, *p);
    /*
    for (int i=0; i<6; i++)
        if (r->pizza[i].db > 0)
        {
            printf("%d. %d ", i, r->futar);
            printf("%d ", r->nap);
            printf("%c ", r->pizza[i].fajta);
            printf("%d \n", r->pizza[i].db);
        }
    */


    *hr = uj_havirendeles(*r);

    kiir(*hr);
    //printf("Rendeles mennyisege: %d\n", hr->mennyiseg);


    return 0;
}


pizza uj_pizza(int db, char fajta) {
    pizza pizza;
    pizza.db = db;
    pizza.fajta = fajta;

    return pizza;
}

rendeles uj_rendeles(int futar, int nap, pizza p) {
    rendeles rendeles;
    rendeles.pizza = malloc(sizeof(pizza) * 6);

    for (int i=0; i<6; i++)
    {
        rendeles.pizza[i].fajta = '\0';
        rendeles.pizza[i].db = 0;
    }

    rendeles.futar = futar;
    rendeles.nap = nap;
    rendeles.pizza[p.fajta - 'A'] = p;

    return rendeles;
}


havirendeles uj_havirendeles(rendeles r) {
    havirendeles h;
    h.rendeles = malloc(sizeof(rendeles));
    h.mennyiseg = 0;

    h.rendeles[h.mennyiseg++] = r;

    return h;
}

void kiir(havirendeles h) {
    for (int i=0; i<h.mennyiseg; i++) {
        printf("Rendeles: %d.\n", i+1);
        printf("\tNap: %d \n", h.rendeles[i].nap);
        printf("\tFutar: %d \n", h.rendeles[i].futar);

        for (int j=0; j<6; j++)
            if (h.rendeles[i].pizza[j].db > 0)
                printf("\t\tPizza: %d %c \n", h.rendeles[i].pizza[j].db, h.rendeles[i].pizza[j].fajta);


    }
}

