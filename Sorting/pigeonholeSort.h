#ifndef PIGEONHOLESORT_H
#define PIGEONHOLESORT_H

#include <stdlib.h>

void pigeonHoleSort (int arr[], int length, const int max_num)
{
    //int pigeonHoleArray[ max_num ];
    int *pigeonHoleArray = malloc(sizeof(arr[0]) * max_num);
    int *temp_array = arr;

    int max_element = 0;
    int min_element = 0;

    int i;
    int range;

    // legkisebb es legnagyobb elemek
    for (i = 0; i < length; i ++)
    {
        if (arr[i] < min_element)
            min_element = arr[i];

        if (arr[i] > max_element)
            max_element = arr[i];
    }

    // tartomany
    range = ( max_element - min_element ) + 1;

    // nullazas
    for ( i = 0; i < range; i++)
        pigeonHoleArray [i] = 0;


    // elemek behelyezese
    for ( i = 0; i < length; i++, temp_array++)
        pigeonHoleArray [ *temp_array - min_element ] += 1;

    // eredeti tombbe visszamasolas
    for (i = 0, temp_array = &arr[0]; i < range; i++)
        while (pigeonHoleArray[i] > 0)
        {
            pigeonHoleArray[i]--;
            *temp_array++ = i + min_element;
        }
}



#endif // PIGEONHOLESORT_H
