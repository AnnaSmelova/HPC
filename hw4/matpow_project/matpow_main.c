#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "matpow_lib.h"


const size_t N = 5;

int main()
{
    double start;
    double end;
    int p = 4;
    
    // A - random matrix
    int *A = (int *) malloc(N * N * sizeof(int));
    RandomMatrix(&A[0], N);

    // C - result matrix
    int *C = (int *) malloc(N * N * sizeof(int));
    ZeroMatrix(&C[0], N);


    printf("Random matrix:\n");
    PrintMatrix(A, N);

    start = omp_get_wtime();
    
    MatPow(&A[0], &C[0], p, N);
    end = omp_get_wtime();

    printf("\nPATH LEN: %d\n", p);
    printf("\nResult Matrix:\n");
    PrintMatrix(C, N);
    
    printf("\nThreads: %d, path_len(p): %d, N: %zu, time: %f seconds\n", omp_get_max_threads(), p, N, (end-start));

    free(A); 
    free(C);
    return 0;
}
