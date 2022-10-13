#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>


void ZeroMatrix(int * A, size_t N)
{
    #pragma omp parallel for shared(A)
    for(size_t i=0; i<N; i++)
    {
        for(size_t j=0; j<N; j++)
        {
            A[i * N + j] = 0;
        }
    }
}

void RandomMatrix(int * A, size_t N)
{
    srand(time(NULL));

    #pragma omp parallel for shared(A)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = (int) (rand() % 2);
        }
    }
}

void MatMul_kij(int * A, int * B, int * C, size_t N)
{

    int *D = (int *) malloc(N * N * sizeof(int));
    ZeroMatrix(&D[0], N);
    
    #pragma omp parallel for shared(A, B, D)
    for (int k = 0; k < N; k++)
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                D[i * N + j] = D[i * N + j] + A[i * N + k] * B[k * N + j];
        }
    }

    #pragma omp parallel for shared(D, C)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i * N + j] = D[i * N + j];
        }
    }
}

void MatPow(int * A, int * C, int p, size_t N)
{
    if (p == 1) 
    {
        #pragma omp parallel for shared(A, C)
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                C[i * N + j] = A[i * N + j];
            }
        }
        return;
    }
 
    MatPow(A, C, p / 2, N);
    MatMul_kij(C, C, C, N);
 
    if (p % 2 != 0)
    {
        MatMul_kij(C, A, C, N);
    }
}

void PrintMatrix(int * A, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", A[N * i + j]);
        }
        printf("\n");
    }
}
