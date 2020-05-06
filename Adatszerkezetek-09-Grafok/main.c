#include <stdio.h>
#include <stdlib.h>


typedef struct elem {
    char adat;
    struct elem *bal;
    struct elem *jobb;
} elem;

typedef elem *binfa;

binfa letrehoz (elem e);
binfa hozzaad (binfa f, elem e);
int hozzafuz(binfa f, elem e);
int nagybetu (char c);
void kiir (binfa f);

int main()
{
    binfa f;
    elem e;

    e.adat = 'a';
    f = letrehoz(e);

    e.adat = 'B';
    f->bal = hozzaad(f,e);
    e.adat = 'c';
    f->jobb = hozzaad(f, e);

    e.adat = 'C';
    hozzafuz(f, e);

    kiir(f);

    return 0;
}

binfa letrehoz(elem e) {
    binfa f = malloc(sizeof(*f));
    f->adat = e.adat;
    f->bal = NULL;
    f->jobb = NULL;
    return f;
}

binfa hozzaad (binfa f, elem e) {
    if (nagybetu(e.adat))
    {
        if (f->bal) {
            hozzaad(f->bal,e);
        }
        if (f->jobb) {
            hozzaad(f->bal,e);
        }
        f = malloc(sizeof(*f));
        f->adat = e.adat;
        f->bal = NULL;
        f->jobb = NULL;
        return f;
    }
    return NULL;
}

int hozzafuz(binfa f, elem e) {
    if (nagybetu(e.adat))
    {
        /*
         * Falucskai tanar ur megoldasa:
        if (!f->bal)
        {
            f->bal = malloc(sizeof(*f));
            f->bal->adat = e.adat;
            f->bal->bal = NULL;
            f->bal->jobb = NULL;
            return 1;
        }
        else
        {
            if (!f->jobb)
            {
                f->jobb = malloc(sizeof(*f));
                f->jobb->adat = e.adat;
                f->jobb->bal = NULL;
                f->jobb->jobb = NULL;
                return 1;
            }
            else
                hozzafuz(f->bal, e);
        }
        */

        if (f->bal)
            hozzafuz(f->bal, e);
        else
        {
            if (f->jobb)
                hozzafuz(f->jobb, e);
            else
            {
                f->jobb = letrehoz(e);
                return 1;
            }
            f->bal = letrehoz(e);
            return 1;
        }
    }
    return 0;
}

int nagybetu (char c) {
    if (c >= 'A' && c<= 'Z')
        return 1;
    return 0;
}

void kiir(binfa f) {
    if (f)
    {
        printf("%c ", f->adat);
        kiir(f->bal);
        kiir(f->jobb);
    }
}

