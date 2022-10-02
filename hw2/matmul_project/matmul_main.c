#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matmul_lib.h"


const size_t N = 500;

int main()
{
    
    int NRuns = 5;

    int a_sizes[] = {500, 512, 1000, 1024, 2000, 2048};

    double *runtimes;
    double *A, *B, *C, *V;
    
    runtimes = (double *) malloc(NRuns * sizeof(double));

    printf("--------------Vector-matrx multiply-------------------\n");

// vector-matrx multiply ij ordering
    double average_runtime = 0.0;
    int size;

    for (int i=0; i<6; i++)
    {
        average_runtime = 0.0;
        size = a_sizes[i];
        A = (double *) malloc(size * size * sizeof(double));
        C = (double *) malloc(size * size * sizeof(double));
        V = (double *) malloc(size * sizeof(double));
        RandomMatrix(&A[0], size);
        RandomVector(&V[0], size);

        for(int n=0; n<NRuns; n++)
        {
            runtimes[n]=CalcMatVecMulTime_ij(&A[0], &V[0], &C[0], size);
            printf("runtime %lf seconds\n", runtimes[n]);
            average_runtime += runtimes[n]/NRuns;
        }

        printf("Size %d: average runtime ij matrix by vector %lf seconds\n", size, average_runtime);
        printf("---------------------------------\n");
    }
    printf("---------------------------------\n");
    printf("---------------Matrix-matrix multiply------------------\n");
    
// matrix-matrix multiply kij ordering
    for (int j=0; j<6; j++)
    {
        average_runtime = 0.0;
        size = a_sizes[j];
        A = (double *) malloc(size * size * sizeof(double));
        B = (double *) malloc(size * size * sizeof(double));
        C = (double *) malloc(size * size * sizeof(double));
        V = (double *) malloc(size * sizeof(double));
        RandomMatrix(&A[0], size);
        RandomMatrix(&B[0], size);
        RandomVector(&V[0], size);

        for(int n=0; n<NRuns; n++)
        {
            runtimes[n]=CalcMatMulTime_kij(&A[0], &B[0], &C[0], size);
            printf("runtime %lf seconds\n", runtimes[n]);
            average_runtime += runtimes[n]/NRuns;
        }
        printf("Size %d: average runtime kij matrix by matrix %lf seconds\n", size, average_runtime);
        printf("---------------------------------\n");
    }
    

    free(A); 
    free(B);
    free(C);
    free(V);
    return 0;
}