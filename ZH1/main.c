#include <stdio.h>
#include <stdlib.h>


/*
 * Specifikáció

A specifikációban a programmal szemben támasztott követelményeket fogalmazzuk meg. A jó specifikáció nem hagy homályosan egyetlenegy részletet sem, bár ilyen ritkán adódik egy bonyolultabb feladat megadása során. Alapvetően tartalmaznia kell az bemenő adatokkal szemben elvárható követelményeket, ezeket előfeltételnek nevezzük

*/


/*
 * Egy gazdának 5 ólja van, mindegyikben maximum 8 darab állatot tart,
mindegyik állatnak van tömege (int) és fajtája, melyet egy karakter jelöl.
*/


// adja meg a gazda, ol és az allat tı́pusokat

typedef struct allat {
    int tomeg;
    char fajta;
} *allat;

typedef struct ol {
    allat allat;
    int mennyiseg;
} *ol;

typedef struct gazda {
    ol ol;
} *gazda;


void kiir(gazda g);
/*
kiı́rja a g gazda állatai adatait (tömeg és fajta). Minden ól tartalma
külön-külön sorba kerüljön, az alábbi módon (vesszők nem fontosak):
1: 2 A, 3 B, 3 B, 6 k
2: 12 f, 31 g, 31 Q, 6 k
3: 5 Z
4:
5: 4 F, 22 C
*/

int mennyi_tomeg(gazda g, ol l);
//kiı́rja, hogy az l ólban lévő állatok össztömegét.


int kivesz(gazda g, allat a);
/*
Kiveszi az ólakból az ”a” állatot és 1-et ad vissza, amennyiben volt
minimum egy ilyen állat. Ha nincs, akkor nem vesz ki semmit sem és
nullát ad vissza.
*/


/*
Algoritmus alg01(X, M, N)
M:=4
ciklus i=N...1
ha (M<=N és X[i]=X[M])
akkor
M:=M+X[i]
ha vége
ciklus vége
Algoritmus vége
*/
void alg01(int X[], int M, int N)
{
    M = 3; // 4 ha nem kell index miatt eltolni 3-ra
    for (int i=N-1; i>=0; i--)
        if (M<=N && X[i] == X[M])
            M += X[i];
}

int main()
{
    gazda g = malloc(sizeof(*g));
    g->ol = malloc(sizeof (ol) * 5);

    for (int i=0; i<5; i++)
    {
        g->ol[i].mennyiseg = 0;
        g->ol[i].allat = malloc(sizeof (allat) * 8);
        for (int j=0; j<8; j++)
        {
            g->ol[i].allat[j].fajta = rand() % 8 + 'A';
            g->ol[i].allat[j].tomeg = rand() % 200;
            g->ol[i].mennyiseg++;
        }
    }

    kiir(g);


    ol l = malloc(sizeof(ol));
    l->allat = malloc(sizeof (allat) * 8);
    for (int j=0; j<8; j++)
    {
        l->allat[j].fajta = rand() % 8 + 'A';
        l->allat[j].tomeg = rand() % 5;
    }
    printf("Tomeg: %d\n\n", mennyi_tomeg(g, l));


    allat a = malloc(sizeof(allat));
    a->fajta = 'B';
    a->tomeg = 200;

    kivesz(g,a);
    kiir(g);

    // free allatok + ol + gazda
    /*
    free(a);
    for (int i=0; i<5; i++)
    {
        //free(g->ol[i].allat);
    }
    free(g->ol);
    free(g);
    */

    return 0;
}

void kiir(gazda g)
{
    for (int o=0; o<5; o++)
    {
        printf("%d: ", o+1);
        for (int a=0; a<7; a++)
            if (g->ol[o].allat[a].tomeg > 0) // letezik az allat
                printf("%d %c, ", g->ol[o].allat[a].tomeg, g->ol[o].allat[a].fajta);
        if (g->ol[o].allat[7].tomeg > 0) // letezik az allat
            printf("%d %c \n", g->ol[o].allat[7].tomeg, g->ol[o].allat[7].fajta); // utolsot vesszo nelkul + uj sor
    }
    printf("\n");
}

int mennyi_tomeg(gazda g, ol l)
{
    int tomeg = 0;

    for (int a=0; a<8; a++)
    {
        tomeg += l->allat[a].tomeg;
    }
    return tomeg;
}

int kivesz(gazda g, allat a)
{
    int szamlal = 0;
    for (int i=0; i<5; i++)
        for (int j=0; j<g->ol[i].mennyiseg; j++)
            if (g->ol[i].allat[j].fajta == a->fajta)
            {
                //g->ol[i].allat[j].fajta = '\0';
                //g->ol[i].allat[j].tomeg = 0;


                g->ol[i].mennyiseg--;

                for (int k=j; j < g->ol[i].mennyiseg; j++)
                {
                    g->ol[i].allat[k].fajta = g->ol[i].allat[k+1].fajta;
                    g->ol[i].allat[k].tomeg = g->ol[i].allat[k+1].tomeg;
                }


                szamlal++;
            }
    if (szamlal) return 1;
    return 0;
}
