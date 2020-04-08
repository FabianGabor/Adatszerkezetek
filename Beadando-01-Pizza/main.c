#include <stdio.h>

typedef struct pizza {
    char fajta;
    int db;
} pizza;

typedef struct rendeles {
    int futar;
    int nap;
    pizza pizza[6];
} rendeles;

typedef struct havirendeles {
    rendeles rendeles[1000];
} havirendeles;

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

int main()
{    
    return 0;
}
