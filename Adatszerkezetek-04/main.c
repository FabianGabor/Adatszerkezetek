#include <stdio.h>
#include <stdbool.h>

int t (char *xi)
{
    if ((*xi>='A') && (*xi<='Z')) return 1;
    return 0;
}

void dontes_2(int n, char *x[], int *van)
{
    int i=0;
    *van = 0;

    while ((!*van) && (i<n))
        if (! t( x[i]))
            i++;
        else
            *van = 1; 
}

void Minden_max_2 (int n, int x[], int *db, int indexek[])
{
    int max = x[0];
    *db = 1;
    indexek[0] = 1;

    for (int i=1; i<n; i++)
    {
        if (max < x[i])
        {
            max = x[i];
            *db = 1;
            indexek[0] = i;
        }
        else
        {
            if (max == x[i])
            {
                indexek[*db] = i;
                db++;
            }
        }
    }
}

int main()
{
    int van;
    van=0;
    char *t[10] = {"teszt1", "Teszt2"};
    dontes_2(2, t, &van);
    printf("Van: %s \n", (van>0)?"van":"nincs");

    int x[] = {2,3,5,4,5,2,9,7,9,4,9};
    int db;
    int ind[11];

    Minden_max_2(11, x, &db, ind);

    printf("Max db: %d\n", db);

    for (int i=0; i<=db; i++)
        printf("%d", ind[i]);

    return 0;
}
