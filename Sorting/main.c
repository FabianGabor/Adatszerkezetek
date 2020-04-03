#include <stdio.h>
#include <pigeonholeSort.h>

void printArr (int arr[], int n)
{
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main()
{
    int arr[] = {8, 3, 2, 7, 4, 6, 8};
    int n = (int) (sizeof(arr) / sizeof(arr[0]));

    printf("Unsorted order is: \n");
    printArr(arr, n);

    pigeonholeSort(arr, n);

    printf("Sorted order is: \n");
    printArr(arr, n);

    return 0;
}
