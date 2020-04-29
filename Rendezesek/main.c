#include <stdio.h>

void beilleszteses(int *t, int n)
{
    int i, j, cs;
    for (i = 1; i < n; i++) {
        cs = t[i];
        j = i - 1;
        while (j >= 0 && t[j] > cs) {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = cs;
    }
}

int main()
{
    printf("Hello World!\n");
    return 0;
}
