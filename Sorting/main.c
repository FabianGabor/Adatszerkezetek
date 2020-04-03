#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pigeonholeSort.h>

#define MAX_NUM 100

typedef struct data {
    int arr10   [   10];
    int arr25   [   25];
    int arr50   [   50];
    int arr100  [  100];
    int arr250  [  250];
    int arr500  [  500];
    int arr1000 [ 1000];
    int arr10000[10000];
} data;

void printArr (int arr[], int n)
{
    for (int i=0; i<n; i++)
        printf("%2d ", arr[i]);
    printf("\n");
}

void randomData ( data *data )
{
    for (int i=0; i<10; i++)
        data->arr10[i] = rand() % MAX_NUM;
}


int main()
{
    /*
    int arr[] = {8, 3, 2, 7, 4, 6, 8};
    int n = (int) (sizeof(arr) / sizeof(arr[0]));

    printf("Unsorted order is: \n");
    printArr(arr, n);

    pigeonholeSort(arr, n);

    printf("Sorted order is: \n");
    printArr(arr, n);
    */

    data data;

    srand(time(NULL));

    clock_t runtime;
    runtime = clock();

    for (int i=0; i<5; i++)
    {
        randomData( &data );
        pigeonHoleSort(data.arr10,10, MAX_NUM);
        printArr(data.arr10, 10);
    }


    runtime = clock() - runtime;
    double time_taken = ((double)runtime)/CLOCKS_PER_SEC; // in seconds
    printf("pigeonholeSort took %f seconds to execute \n", time_taken);


    return 0;
}
