#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float log_2 (float x)
{

    return log10(x) / log10(2);
}

float e (float *t, int n)
{
    int i;
    float e = 0;
    for (i=0; i<n; i++)
        e += t[i] * log_2(1 / t[i]);
    return e;
}

double f02 (int n)
{
    return pow( (1.0 + 2.0/n), n);
}

float randomgen (int lower, int upper)
{
    return (((rand() % (upper - lower + 1)) + lower) );
}

int main()
{
    // 1.
    printf("\n1.:\n");
    int n = 100;
    float t[100] = {0};
    int upper = 1000;
    int lower = 1;

    for (int i=0; i<n; i++)
    {
        t[i] = randomgen (lower, upper) / 1000;
        printf("%3f3 ", t[i]);
    }
    printf("\ne = %f\n", e(t,5));


    // 2.
    printf("\n2.:\n");
    n = 10; // n>=1
    for (int i = 1; i <= n; i++)
        printf("%f \n", f02(i));


    // 3.
    printf("\n3.:\n");
    float tmp = f02(1), result = 0;
    n = 1;
    do
    {
        tmp = result;
        n++;
        result = pow( (1.0 + 2.0/n), n);
    }
    while (result - tmp > 0.000000001);

    printf("%f\n", result);

    return 0;
}
