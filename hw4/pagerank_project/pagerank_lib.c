#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>


void MatVecMul(double *A, double *B, double *C, int N) 
{
	#pragma omp parallel for shared(A, B, C, N)
    for (int i = 0; i < N; ++i) {
        C[i] = 0;
        for (int j = 0; j < N; ++j)
        {
        	C[i] += A[i * N + j] * B[j];
        }
    }
}

double L1_Norm(double *A, double *B, int N) 
{
	double norm = 0;
	#pragma omp parallel for shared(A, B, N) reduction(+:norm)
    for (int i = 0; i < N; ++i)
    {
        norm += fabs(A[i] - B[i]);
    }
    return norm;
}

void PageRank(double *A, double *C, int N) 
{
	double eps = 1e-6;
    double damp = 0.8;
    int iter_limit = 1e6;
    double *A_norm = (double *) malloc(N * N * sizeof(double));
	double s;
	int i, j;

	#pragma omp parallel for shared(A, A_norm, N)
    for (i = 0; i < N; i++) 
    {
    	s = 0;
    	for (j = 0; j < N; j++) 
        {
    		s += A[j * N + i];
    	}
    
    	for (j = 0; j < N; j++) 
        {
    		if (s != 0)
            {
    			A_norm[j * N + i] = A[j * N + i] / s;
            }
    		else 
            {
    			A_norm[j * N + i] = 0;
            }
    	}
    }

    double *B = (double *) malloc(N * sizeof(double));
    #pragma omp parallel for shared(B, N)
    for (i = 0; i < N; ++i) 
    {
    	B[i] = 1.0 / N;
    }

    for (i = 0; i < iter_limit; ++i) 
    {
    	MatVecMul(A_norm, B, C, N);
    	for (j = 0; j < N; ++j) {
    		C[j] = ((1 - damp) / N) + (damp * C[j]);
    	}

    	if (L1_Norm(B, C, N) < eps)
    		break;

    	memcpy(B, C, N * sizeof(double));
    }
    free(A_norm);
    free(B);
}

void NaiveRank(double *A, double *C, int N)
{
    int i,j;

    #pragma omp parallel for shared(A, C, N)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[j] += A[j * N + i];
        }
    }
}
