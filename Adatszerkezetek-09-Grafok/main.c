#include <stdio.h>
#include <stdlib.h>

typedef char elem;
typedef struct binfa {
    elem e;
    struct binfa *bal;
    struct binfa *jobb;
} *binfa;

void letrehoz (elem e);
void kiir (binfa f);

int main()
{
    binfa f = malloc(sizeof(*f));
    return 0;
}
