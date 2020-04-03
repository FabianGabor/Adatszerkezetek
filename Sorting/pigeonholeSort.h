#ifndef PIGEONHOLESORT_H
#define PIGEONHOLESORT_H

void pigeonholeSort(int *array, int n)
{
    int *arr;
    arr = array;

    int min = arr[0];
    int max = arr[0];
    int range, i, j, index = 0;

    for (int a=0; a<n; a++)
    {
        if (arr[a] > max)
            max = arr[a];
        if (arr[a] < min)
            min = arr[a];
    }

    range = max - min + 1;
    int phole[range];

    for (i = 0; i<range; i++)
        phole[i] = 0;

    for (i = 0; i<range; i++)
        phole[arr[i] - min]++;

    for (j=0; j<range; j++)
        while(phole[j]-- > 0)
            arr[index++] = j + min;
}

void pigeonHoleSort (int arr[], int length, const int max_num)
{
    int pigeonHoleArray[ max_num ];
    int *temp_array = arr;

    int max_element = 0;
    int min_element = 0;

    int i;
    int range;

    // Get the min_element and max_element from the given array
    for (i = 0; i < length; i ++)
    {
        if (arr[i] < min_element)
            min_element = arr[i];

        if (arr[i] > max_element)
            max_element = arr[i];
    }

    // Get the range
    range = ( max_element - min_element ) + 1;

    // Initialize the pigeonHoleArray with zero
    for ( i = 0; i < range; i++)
        pigeonHoleArray [i] = 0;


    // place the elements in pigeonHoleArray
    for ( i = 0; i < length; i++, temp_array++)
        pigeonHoleArray [ *temp_array - min_element ] += 1;

    // copy from pigeonHoleArray to original array
    for (i = 0, temp_array = &arr[0]; i < range; i++)
        while (pigeonHoleArray[i] > 0)
        {
            pigeonHoleArray[i]--;
            *temp_array++ = i + min_element;
        }
}



#endif // PIGEONHOLESORT_H
