#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>
#include "pagerank_lib.h"


int main() 
{
	FILE *stations_matrix = fopen("../stations_matrix.txt", "r");
	int num;
	int N = 194;
	double *A = (double *) malloc(N * N * sizeof(double));
    double *C = (double *) malloc(N * sizeof(double));
    double *C_naive = (double *) malloc(N * sizeof(double));

	if(stations_matrix == NULL) 
    {
        printf("Bad filepath!\n");
        exit(1);
    }

    int i = 0;
    while(fscanf(stations_matrix, "%d", &num) != EOF ) 
    {
    	A[i] = num;
        i++;
    }
    fclose(stations_matrix);

    PageRank(A, C, N);

    double sum = 0;
    double max_pr = 0;
    int max_ind = 0;
    printf("Final PageRank:\n");
    for (i = 0; i < N; ++i)
    {
        printf("%2d: %f ", i, C[i]);
        if (max_pr < C[i])
        {
            max_pr = C[i];
            max_ind = i;
        }
        sum += C[i];
    }
    printf("\nsum: %f\n", sum);
    printf("max ind: %d\n", max_ind);

    NaiveRank(A, C_naive, N);

    sum = 0;
    max_pr = 0;
    max_ind = 0;
    printf("Final NaiveRank:\n");
    for (i = 0; i < N; ++i)
    {
        printf("%2d: %f ", i, C_naive[i]);
        if (max_pr < C_naive[i])
        {
            max_pr = C_naive[i];
            max_ind = i;
        }
        sum += C_naive[i];
    }
    printf("\nsum: %f\n", sum);
    printf("max ind: %d\n", max_ind);

    free(A);
    free(C);
    free(C_naive);

    return 0;
}
