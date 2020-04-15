#include <stdio.h>

typedef struct verem
{
    char v[10];
    int baldb,jobbdb;
} verem;

int betesz(verem *v, char x)
{
    if (x>='A'&& x<='Z')
    {
        v->baldb=1;
        v->v[0]=x;
        return 1;
    }
    else
        if (x>='0' && x<='9')
        {
            v->jobbdb=1;
            v->v[9]=x;
            return 1;
        }
    return 0;
}

int main()
{
    verem a;
    a.baldb=0;
    a.jobbdb=0;
    int i;

    for(i=0;i<10;i++)
        a.v[i]='_';

    char be=getchar();
    betesz(&a,be);

    /*
    if (be>='A'&&be<='Z')
    {
        a.baldb=1;
        a.v[0]=be;
    }
    else
        if (be>='0'&&be<='9')
        {
            a.jobbdb=1;
            a.v[9]=be;
        }
    */

    printf("\nA verem tartalma: ");

    printf("|");
    for(i=0; i<10; i++)
        printf("%c", a.v[i]);
    printf("|\n");

    return 0;
}
