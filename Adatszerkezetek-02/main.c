#include <stdio.h>
#include <string.h>

typedef int tarto[6];

void kiir (tarto t)
{
    for (int i=1; i<=t[0]; i++)        
        printf("%c", t[i] + 'A');
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
        return 0;
}

int kivesz (tarto t)
{
    if (t[0]>0)
    {
        t[0]--;
        return t[t[0] + 1];
    }
    else    
        return 0;
}

void beker (tarto t)
{
    char input[11] = "EAOOOABO";
    //printf("Kerem a jelsorozatot: ");
    //scanf("%s", input);
    printf("%d %s \n", (int)strlen(input), input);

    // int tmp[6] = {0, -1, -1, -1, -1, -1}; // DEBUG

    for (int i=0, j=1; i<(int)strlen(input); /*increment inside by 1 or by number of O's */ )
    {
        //char input_i = input[i]; // DEBUG

        if (input[i] != 'O')
        {
            betesz(t, input[i] - 'A');
            //tmp[0]++; // DEBUG
            //tmp[t[0]] = t[t[0]]; // DEBUG
        }
        else
        {
            while (input[i+j-1] == 'O' && i-j>=0)
            {
                j++;
                printf("%c", 'A' + kivesz(t));
                //tmp[0]--; // DEBUG
            }
            j--;
        }
        i+=j;
    }
    printf("\n");
}

int main()
{
    tarto t = {0};

    beker(t);
    printf("Megmaradt sorozat: ");
    kiir(t);

    return 0;
}
