#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

// Ha egy sorozat minden minimális elemének az indexét meg szeretnénk határozni, akkor kénytelenek vagyunk legalább kétszer végigvenni a sorozat elemeit.
// Bizonyitas az ellenkezojerol

// 1 bejarassal elmenti a minimum ertekek indexeit (0-tol szamozva).
// minimumok szama maximum annyi lehet, mint a vizsgalt sorozat elemeinek szama, ezert van min[N]

void kiir(int a[], int n)
{
    for (int i=0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int a[N], min[N];
    int min_count = 0;

    srand(time(NULL));
    for (int i=0; i<N; i++)
    {
        a[i] = rand() % 10;
        min[i] = 0;
    }

    kiir(a, N);

    // minimum indexek keresese
    min[min_count] = 0;
    for (int i=1; i<N; i++)
    {
        if (a[i] < a[min[min_count]])
        {
            min_count = 0;
            min[min_count] = i;
        }
        else
            if (a[i] == a[min[min_count]])
            {
                min_count++;
                min[min_count] = i;
            }
    }
    min_count++;

    kiir(min, min_count);

    return 0;
}
