#include <stdio.h>
#include <stdlib.h>

typedef struct verem
{
    char v[10];
    int baldb,jobbdb;
} *verem;

int betesz(verem v, char x)
{
    if (v->baldb + v->jobbdb >= (int)sizeof(v->v))
        return 0;
    if (x>='A'&& x<='Z')
    {
        v->v[v->baldb++]=x;
        return 1;
    }
    else
        if (x>='0' && x<='9')
        {
            v->v[sizeof(v->v)-1 - v->jobbdb++]=x;
            return 1;
        }
    return 0;
}

int main()
{
    verem a = malloc(sizeof(verem));
    int bufferOverflow = 0;

    a->baldb=0;
    a->jobbdb=0;

    int i;

    for(i=0;i<10;i++)
        a->v[i]='_';

    //printf("Karakter: ");
    //char be=getchar();

    char str[] = "A43QHG54W4GRASDFG5213";
    int size = sizeof(str)-1;
    for (i=0; i<size; i++)
        if (!betesz(a,str[i]))
            bufferOverflow++;

    printf("\nA verem tartalma: ");

    printf("|");
    for(i=0; i<15; i++)
        printf("%c", a->v[i]);
    printf("|\n");

    printf("Tulcsordult %d\n", bufferOverflow);

    return 0;
}
