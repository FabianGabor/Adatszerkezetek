#include <stdio.h>
#include <string.h>

#define vegtelen __INT_MAX__

void Osszefesul_2(int N, int X[], int M, int Y[], int *db, int Z[]) {
    *db=0;
    int i=0;
    int j=0;
    while (i<N && j<M) {
       if (X[i] < Y[j]) {
          Z[*db] = X[i];
          i+=1;
       }
       else {
           if (X[i] == Y[j]) {
              Z[*db] = X[i];
              i++;
              j++;
           } else {
              Z[*db]=Y[j];
              j++;
           }
       }
       *db+=1;
    }
    while (i<N) {
       Z[*db]=X[i];
       *db+=1;
       i++;
    }
    while (j<M) {
       Z[*db]=Y[j];
       *db+=1;
       j++;
    }
}

void Osszefesul_4(int n, int X[], int m, int Y[], int *db, int Z[])
{
    *db = 0;
    int i = 0;
    int j = 0;
    X[n] = vegtelen;
    Y[m] = vegtelen;

    while (i<n || j<m) {

        if (X[i] < Y[j]) {
            Z[*db] = X[i];
            i+=1;
        }
        else
            if (X[i] == Y[j]) {
                Z[*db] = X[i];
                i+=1;
                j+=1;
            }
            else {
                Z[*db] = Y[j];
                j+=1;
            }
        *db+=1;
    }
}


int T(char *X) {
    //return 0;
    return strcmp(X,"alma");
}

void Szetvalogatas_1(int N, char **X, int *dby, char **Y, int *dbz, char **Z) {
   *dby = 0;
   *dbz = 0;
   for (int i=0; i<N; i++) {
       if (T(X[i])) {
        Y[*dby] = X[i];
        *dby += 1;
       }
      else {
        Z[*dbz] = X[i];
        *dbz += 1;
      }
   }
}


void kiir(char **tomb, int n)
{
    for (int i=0; i<n; i++)
        printf("%s\n",tomb[i]);
    printf("\n");
}


int main()
{
    /*
    int t1[] = {8, 23, 11,0};
    int t2[] = {7, 8, 5, 23,0};
    int t3[10];//a nulla a végtelennek foglalja a helyet
    int n1 = 3;
    int n2 = 4;
    int n3 = 0;


    Osszefesul_2(n1, t1, n2, t2, &n3, t3);
    printf("n3 = %d\n", n3);
    for(int i=0; i<n3-1; i++)
        printf("%d, ",t3[i]);
    printf("%d\n",t3[n3-1]);


    Osszefesul_4(n1, t1, n2, t2, &n3, t3);
    printf("n3 = %d\n", n3);
    for(int i=0; i<n3-1; i++)
        printf("%d, ",t3[i]);
    printf("%d\n",t3[n3-1]);
    */


    int N = 3;
    int dby;
    int dbz;

    char *X[]={"alma", "korte","szilva"};
    char *Y[3];
    char *Z[3];

    //kiir(X);

    Szetvalogatas_1(N, X, &dby, Y, &dbz, Z);
    kiir(X, N);
    kiir(Y, dby);
    kiir(Z, dbz);

    return 0;
}
