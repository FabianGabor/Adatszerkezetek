#ifndef MSDSORT_H
#define MSDSORT_H

#include <stdlib.h>
#include <string.h>

typedef char *String;
typedef String *StringArr;


int less(String s, String t, int d)
{
    if ((int)strlen(t) <= d) return 0;
    if ((int)strlen(s) <= d) return 1;
    return s[d] < t[d];
}

int equal(String s, String t, int d)
{
    return !less(s, t, d) && !less(t, s, d);
}


void swap(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

void exch(StringArr str, int i, int j)
{
    swap(str[i], str[j]);
}

void StrSort(String a[], int l, int r, int d)
{
    if (r <= l) return;
    String v = a[r];
    int i = l-1, j = r, p = l-1, q = r, k;

    while (i < j)
    {
        while (less(a[++i], v, d)) ;
        while (less(v, a[--j], d))
            if (j == l) break;
        if (i > j) break;
        exch(a, i, j);
        if (equal(a[i], v, d)) exch(a, ++p, i);
        if (equal(v, a[j], d)) exch(a, --q, j);
    }
    if (p == q)  // first d+1 chars of all keys equal
        if ((int)strlen(v) > d) StrSort(a, l, r, d+1);
    if (p == q) return;
    if (less(a[i], v, d)) i++;

    for (k = l; k <= p; k++, j--) exch(a, k, j);
    for (k = r; k >= q; k--, i++) exch(a, k, i);

    StrSort(a, l, j, d);

    if ((i == r) && (equal(a[i], v, d))) i++;
    if ((int)strlen(v) >= d) StrSort(a, j+1, i-1, d+1);

    StrSort(a, i, r, d);
}


#endif // MSDSORT_H
