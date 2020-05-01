#ifndef THREEWAYRADIXQSORT_H
#define THREEWAYRADIXQSORT_H

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <typedef.h>



// 3-way radix quicksort
int CUTOFF =  15;   // cutoff to insertion sort



char* substring(const char *src, int m, int n)
{
    // get length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

// return the dth character of s, -1 if d = length of s
int charAt(String s, int d) {
    //assert( d >= 0 && d <= (int)strlen(s));
    if (d == (int)strlen(s)) return -1;
    return s[d];
}

// is v less than w, starting at character d
static int less(String v, String w, int d) {
    for (int i = d; i < (int) min(strlen(v), strlen(w)); i++) {
        if (charAt(v, i) < charAt(w, i)) return 1;
        if (charAt(v,i) > charAt(w,i)) return 0;
    }
    return strlen(v) < strlen(w);
}

// is the array sorted
static int isSorted(lista a, int rows) {
    int i = 1;
    for (i = 1; i < rows; i++)
    {
       if (strcmp(a[i].nev,a[i-1].nev) < 0) return 0;
    }

    return 1;
}

// exchange a[i] and a[j]
static void exch(lista a, int i, int j) {
    szemely temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// sort from a[lo] to a[hi], starting at the dth character
static void insertion(lista a, int lo, int hi, int d) {
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && less(a[j].nev, a[j-1].nev, d); j--)
            exch(a, j, j-1);
}



// 3-way string quicksort a[lo..hi] starting at dth character


static void sort(lista a, int lo, int hi, int d){

    // cutoff to insertion sort for small subarrays
    if (hi <= lo + CUTOFF) {
        insertion(a, lo, hi, d);
        return;
    }


    if (hi<=lo) return;
    int lt = lo, gt = hi, i=lo+1; // use 3 pointers: lt, i, gt
    char pivot = charAt(a[lo].nev,d);
    while(i<=gt) //invariant: a[lo,lt)<pivot, a(gt,hi]>pivot, a[lt,i]=pivot
    {
        char c = charAt(a[i].nev,d);
        if(c<pivot)
            exch(a,lt++,i++);
        else
            if(c>pivot) exch(a,i,gt--);
            else i++;
    }//3-way partition
    sort(a,lo,lt-1,d);
    if(pivot>=0) sort(a,lt,gt,d+1);//pivot<0 means end-of-string
    sort(a,gt+1,hi,d);
}

void reverse(lista a, unsigned int letszam)
{
    if (a == NULL || letszam < 2)
        return;

    for (unsigned int i = 0; i < letszam / 2; i++)
    {
        szemely temp = a[i];
        a[i] = a[letszam - 1 - i];
        a[letszam - 1 - i] = temp;
    }
}


void sortNev(lista a, unsigned int rows)
{
    sort(a, 0, rows-1, 0);
    assert (isSorted(a, rows));
}

#endif // THREEWAYRADIXQSORT_H
