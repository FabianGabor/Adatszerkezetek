#include <stdio.h>
#include <strings.h>

typedef int tarto[6];

void kiir (tarto t)
{
    for (int i=1; i<=t[0]; i++)
        //printf("%d ", t[i]);
        printf("%c ", t[i] + 'A');
    printf("\n");
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

void beker (tarto t)
{
    char input[11] = "EABCDAAOOO";
    //printf("Kerem a jelsorozatot: ");
    //scanf("%s", input);
    printf("%d %s \n", (int)strlen(input), input);

    t[0] = 0;

    for (int i=0; i<(int)strlen(input); /*increment inside by 1 or by number of O's */ )
    {
        int j=1;
        for (;input[i+j-1] == 'O' && i-j>=0; j++)
        {
            printf("%c", input[i-j]);
        }
        i=i+j;
    }
    printf("\n");
}

int main()
{
    //tarto t = {2,0,1};
    tarto t = {0};

    /*
    for (int i=0; i<6; i++)
        printf("%d ", t[i]);
    printf("\n");
    */
    //kiir(t);

    //betesz(t, 'A' - 65);
    //kiir(t);

    beker(t);

    return 0;
}
