#ifndef TIMSORT_H
#define TIMSORT_H

#include <typedef.h>

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

const int RUN = 32;

int kor(szemely a) {
    return (a.szulDatum.ev - 1900) * 365 + a.szulDatum.ho * 30 + a.szulDatum.nap;
}

void insertionSort(lista arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        szemely temp = arr[i];
        int j = i - 1;
        while (kor(arr[j]) > kor(temp) && j >= left)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

void merge(lista arr, int l, int m, int r)
{
    int len1 = m - l + 1, len2 = r - m;
    szemely left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2)
    {
        if (kor(left[i]) <= kor(right[j]))
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1)
    {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2)
    {
        arr[k] = right[j];
        k++;
        j++;
    }
}

void timSort(lista arr, int n)
{
    for (int i = 0; i < n; i+=RUN)
        insertionSort(arr, i, min((i+31), (n-1)));

    for (int size = RUN; size < n; size = 2*size)
    {
        for (int left = 0; left < n; left += 2*size)
        {
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), (n-1));

            merge(arr, left, mid, right);
        }
    }
}

#endif // TIMSORT_H
