#include <stdio.h>

typedef int tarto[6];

void kiir (tarto t)
{
    for (int i=1; i<=t[0]; i++)
        printf("%d ", t[i]);
}

int betesz (tarto t, int x)
{
    if (t[0]<5)
    {
        t[ t[0] + 1] = x;
        t[0]++;
        return 1;
    }
    else
    {
        return 0;
    }
}

int kivesz (tarto t)
{
    if (t[0]>0)
    {
        t[0]--;
        return t[t[0] + 1];
    }
    else
    {
        return 0;
    }
}

int main()
{
    tarto t = {2,12,25};

    for (int i=0; i<6; i++)
        printf("%d ", t[i]);
    printf("\n");

    kiir(t);

    return 0;
}
