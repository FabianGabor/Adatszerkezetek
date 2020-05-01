#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef char nev[30];
typedef unsigned int ev;
typedef unsigned int ho;
typedef unsigned int nap;

typedef struct szulDatum {
    ev ev;
    ho ho;
    nap nap;
} szuldatum;

typedef struct szemely {
    nev nev;
    szuldatum szulDatum;
} szemely;

typedef szemely *lista;

typedef char *String;
typedef String *StringArr;

#endif // TYPEDEF_H
