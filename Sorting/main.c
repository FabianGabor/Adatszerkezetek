#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigeonholeSort.h>
//#include <quicksort.h>
#include <timsort.h>

#include <string.h>
#include <assert.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define NUM_RUNS 1000

#define RANGE (int) pow('Z'-'A' + 'z' - 'a',3)
#define N 1000

#define ROWS 1000


typedef int *array;

void printArr (int arr[], int n)
{
    printf("\n");
    for (int i=0; i<n; i++)
        printf("%3d ", arr[i]);
    printf("\n\n");
}

array randomData (int n)
{
    array array = malloc(sizeof (*array) * n);
    for (int i=0; i<n; i++)
        array[i] = rand() % RANGE;
    return array;
}








/*********************************************************/
typedef char *String;
typedef String *StringArr;


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
// DEPRECATED BECAUSE OF SLOW SUBSTRING EXTRACTION IN JAVA 7
// private static boolean less(String v, String w, int d) {
//    assert v.substring(0, d).equals(w.substring(0, d));
//    return v.substring(d).compareTo(w.substring(d)) < 0;
// }

// is v less than w, starting at character d
static int less(String v, String w, int d) {

    //assert ( strcmp(substring(v, 0, d), (substring(w, 0, d))) );


    for (int i = d; i < (int) min(strlen(v), strlen(w)); i++) {
        if (charAt(v, i) < charAt(w, i)) return 1;
        if (charAt(v,i) > charAt(w,i)) return 0;
    }
    return strlen(v) < strlen(w);
}

// is the array sorted
static int isSorted(StringArr a) {
    for (int i = 1; i < (int)sizeof(a); i++)
        if (strcmp(a[i],a[i-1]) < 0) return 0;

    return 1;
}

// exchange a[i] and a[j]
static void exch(StringArr a, int i, int j) {
    String temp = malloc(sizeof(char) * 500);
    strcpy(temp, a[i]);
    a[i] = a[j];
    a[j] = temp;
}

// sort from a[lo] to a[hi], starting at the dth character
static void insertion(StringArr a, int lo, int hi, int d) {
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && less(a[j], a[j-1], d); j--)
            exch(a, j, j-1);
}



// 3-way string quicksort a[lo..hi] starting at dth character
static void sort1(StringArr a, int lo, int hi, int d) {


    // cutoff to insertion sort for small subarrays
    if (hi <= lo + CUTOFF) {
        insertion(a, lo, hi, d);
        return;
    }

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v)
            exch(a, lt++, i++);
        else
            if (t > v)
                exch(a, i, gt--);
            else
                i++;
    }

    // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
    sort1(a, lo, lt-1, d);
    if (v >= 0) sort1(a, lt, gt, d+1);
    sort1(a, gt+1, hi, d);
}



static void sort2(StringArr a, int lo, int hi, int d){

    // cutoff to insertion sort for small subarrays
    if (hi <= lo + CUTOFF) {
        insertion(a, lo, hi, d);
        return;
    }


    if (hi<=lo) return;
    int lt = lo, gt = hi, i=lo+1; // use 3 pointers: lt, i, gt
    char pivot = charAt(a[lo],d);
    while(i<=gt) //invariant: a[lo,lt)<pivot, a(gt,hi]>pivot, a[lt,i]=pivot
    {
        char c = charAt(a[i],d);
        if(c<pivot)
            exch(a,lt++,i++);
        else
            if(c>pivot) exch(a,i,gt--);
            else i++;
    }//3-way partition
    sort2(a,lo,lt-1,d);
    if(pivot>=0) sort2(a,lt,gt,d+1);//pivot<0 means end-of-string
    sort2(a,gt+1,hi,d);
}


static void sortString1(StringArr a) {
    sort1(a, 0, ROWS-1, 0);
    assert (isSorted(a));
}
static void sortString2(StringArr a) {
    sort2(a, 0, ROWS-1, 0);
    assert (isSorted(a));
}





int main()
{
    clock_t runtime;
    double time_taken_Tim, time_taken_Pigeon, time_taken_strings;
    srand(time(NULL));

    /*
    array arr = malloc(sizeof (*arr) * N);
    array randarr = malloc(sizeof (*randarr) * N);

    printf("Range: %d\n", RANGE);

    randarr = randomData(N);
    //printArr(randarr,N);



    runtime = clock();
    for (int i=0; i<NUM_RUNS; i++)
    {
        memcpy(arr,randarr,sizeof(*randarr) * N);
        timSort(arr,N);
    }
    runtime = clock() - runtime;
    time_taken_Tim = ((double)runtime)/CLOCKS_PER_SEC; // in seconds

    printf("Timsort %f seconds to sort.\n", time_taken_Tim);



    runtime = clock();
    for (int i=0; i<NUM_RUNS; i++)
    {
        memcpy(arr,randarr,sizeof(*randarr) * N);
        pigeonHoleSort(arr, N, RANGE);
    }
    runtime = clock() - runtime;
    time_taken_Pigeon = ((double)runtime)/CLOCKS_PER_SEC; // in seconds
    printf("Pigeon  %f seconds to sort.\n", time_taken_Pigeon);


    printf("\n%s\n", (time_taken_Tim < time_taken_Pigeon) ? "Timsort faster" : "Pigeon faster");
*/



    const int rows = 1000;
    StringArr str1 = malloc(rows * sizeof(char*));
    StringArr str2 = malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; i++)
    {
        str1[i] = malloc(sizeof(char) * 500);
        str2[i] = malloc(sizeof(char) * 500);
    }


    FILE *f = fopen("MOCK_DATA.csv", "r");
    char * line = NULL;
    ssize_t read;
    size_t len = 0;



    for (unsigned int i=0; (read = getline(&line, &len, f)) != -1; i++)
    {
        str1[i] = malloc(sizeof(char) * 500);
        str2[i] = malloc(sizeof(char) * 500);
        strcpy(str1[i], line);
        strcpy(str2[i], line);
    }
    fclose(f);
    if (line)
    free(line);


    /*
    for (int i = 0; i < rows; i++)
        printf("%s", str[i]);
    printf("\n\n\n");
    */


    runtime = clock();
    // sort the strings
    sortString1(str1);
    runtime = clock() - runtime;
    time_taken_strings = ((double)runtime)/CLOCKS_PER_SEC; // in seconds
    printf("%f seconds to sort %d strings.\n", time_taken_strings, rows);


    /*
    for (int i = 0; i < rows; i++)
        printf("%s", str[i]);
    printf("\n");
    */



    runtime = clock();
    // sort the strings
    sortString2(str2);
    runtime = clock() - runtime;
    time_taken_strings = ((double)runtime)/CLOCKS_PER_SEC; // in seconds
    printf("%f seconds to sort %d strings.\n", time_taken_strings, rows);


    return 0;
}
