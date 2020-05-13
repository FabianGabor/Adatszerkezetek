/* Fábián Gábor
 * CXNU8T
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct tag
{
  int data;
  struct tag *bal;
  struct tag *jobb;
};

struct elem1 {
    int adat;
    struct elem1 *kov;
};

struct tag *ujElem(int data);
int szumma_bin(struct tag * elso);
int darab(struct elem1 * gy);

void tombosalg(int X[], int N, int Y[], int M, int Z[], int P, int Q)
{
    int i = 1;
    int j = Q;
    int k = 0;
    while (i <= M && j <= N)
    {
        if (X[j] == Y[i])
        {
            k++;
            Z[k] = i;
        }
        i++;
    }
    P = k;
}

/*
Írjon függvényt, mely egy karakterekből álló N elemű X tömb elemeit
kettesével megcserélgeti. Ha az elemek száma nem osztható kettővel,
akkor az utolsó elem helyben marad:ABCDEFG⇒BADCFEG void
csere(char * X, int N). Feltehetjük, hogy legalább egy elem van
a tömbben.
*/

void csere(char *X, int N)
{
    char tmp = 0;
    for (int i = 0; i < N-1; i+=2)
    {
        tmp = X[i];
        X[i] = X[i+1];
        X[i+1] = tmp;
    }
}

struct elem2
{
    char betu;
    struct elem2 *m1;
};

/*
Írjon függvényt, mely betesz egy elemet a SOR viselkedésű láncolt adat-
szerkezetbe, X a sor első elemének mutatója, és ı́rni a sor végére szabad
csak! Feltehetjük, hogy nem üres a sor.
*/
void berak(struct elem2 *X, char ujbetu);


void kiir(struct elem2 *X2)
{
    while (X2 != NULL)
    {
        printf("%c ", X2->betu);
        X2 = X2->m1;
    }
    printf("\n");
}

int main()
{
    //struct tag *gyoker = ujElem(1);
    struct tag *gyoker = ujElem(10);
    gyoker->bal = ujElem(20);
    gyoker->jobb = ujElem(30);
    gyoker->jobb->bal = ujElem(40);

    printf("%d\n", szumma_bin(gyoker));


    struct elem1 *lista = malloc(sizeof(*lista));
    lista->adat = 10;
    lista->kov = malloc(sizeof(*lista));
    lista->kov->adat = 20;
    lista->kov->kov = NULL;

    printf("%d\n", darab(lista));

    int N;
    char X[] = "ABCDEFG";
    N = sizeof (X) - 1;

    for (int i=0; i<N; i++)
        printf("%c ", X[i]);
    printf("\n");

    csere(X, N);

    for (int i=0; i<N; i++)
        printf("%c ", X[i]);
    printf("\n");

    struct elem2 *X2 = malloc(sizeof(*X2));
    X2->betu = 'a';
    X2->m1 = NULL;

    kiir(X2);
    berak(X2, 'b');
    kiir(X2);

    return 0;
}

struct tag *ujElem(int data)
{
    struct tag *uj = (struct tag*)malloc(sizeof(*uj));
    uj->data = data;
    uj->bal = NULL;
    uj->jobb = NULL;
    return(uj);
}

int szumma_bin(struct tag *elso)
{
    int sum = 0;
    if(elso != NULL)
    {
        sum = (elso->data) + szumma_bin(elso->bal) + szumma_bin(elso->jobb);
        return sum;
    }
    return 0;
}

int darab(struct elem1 * gy)
{
    int db = 0;
    struct elem1* elem = gy;
    while (elem != NULL)
    {
        db++;
        elem = elem->kov;
    }
    return db;
}

void berak(struct elem2 *X, char ujbetu)
{
    struct elem2* uj_elem = (struct elem2*) malloc(sizeof(struct elem2));
    struct elem2 *utolso = X;

    uj_elem->betu  = ujbetu;
    uj_elem->m1 = NULL;

    if (X == NULL)
    {
       X = uj_elem;
       return;
    }

    while (utolso->m1 != NULL)
        utolso = utolso->m1;

    utolso->m1 = uj_elem;
}
