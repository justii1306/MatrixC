#include <stdio.h>
#include <stdlib.h>

double det(double ** matrix, int rozmiar);

double ** matrix_alloc(int x)
{
    int o;
    double **alokacja = (double **)malloc(x * sizeof(double*));
	for(o=0; o<x; o++)
        alokacja[o] = (double *)malloc(x * sizeof(double));
    return alokacja;
}

void matrix_free(double ** matrix, int r)
{
    int k;
    for(k=0; k<r; k++)
        free(matrix[k]);
    free(matrix);
}

double det(double ** matrix, int rozmiar)
{
    double sum=0.0;
    int sign=1;
    int i, u, v;
    double **fminor;
    if(rozmiar==1)
        sum = matrix[0][0];
    if(rozmiar==2)
        sum = matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    if(rozmiar>=3){
        fminor=matrix_alloc(rozmiar-1);
        for(i=0;i<rozmiar;i++){
            for(v=0; v<rozmiar-1; v++){
                for(u=0; u<i; u++)
                    fminor[v][u]=matrix[v+1][u];
                for(u=i+1; u<rozmiar; u++)
                    fminor[v][u-1]=matrix[v+1][u];
             }
            sum+=sign*matrix[0][i]*det(fminor, rozmiar-1);
            sign=-sign;
         }
        matrix_free(fminor, rozmiar-1);
      }
    return sum;
}

int main()
{
    int rozmiar, i, j;
    double wynik;
    double ** fmacierz;
    FILE *fp;
    fp=fopen("macierz.txt", "r");
    if (fp==NULL){
    printf("Błąd odczytu pliku\n");
    return 1;
    }
    fscanf(fp, "%d", &rozmiar);
    fmacierz=matrix_alloc(rozmiar);
    for (i=0; i<rozmiar; i++){
       for (j=0; j<rozmiar; j++){
           fscanf(fp, "%lf", &fmacierz[i][j]);
       }
    }
    wynik=det(fmacierz, rozmiar);
    printf("Wyznacznik podanej macierzy jest równy: %.1lf\n",wynik);
    fclose(fp);
    matrix_free(fmacierz, rozmiar);
    return 0;
}
