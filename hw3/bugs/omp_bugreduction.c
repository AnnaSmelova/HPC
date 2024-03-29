#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float * a, float * b, size_t N)
{
    int tid;
    float sum = 0.0;

    //tid = omp_get_thread_num();

    #pragma omp parallel for reduction(+:sum) private(tid)
    for (int i = 0; i < N; ++i)
    {
        tid = omp_get_thread_num();
        sum += a[i] * b[i];
        printf("tid = %d i = %d\n", tid, i);
    }

    return sum;
}

int main (int argc, char *argv[])
{
    const size_t N = 100;
    int i;
    float sum;
    float a[N], b[N];


    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double)i;
    }

    sum = dotprod(a, b, N);

    printf("Sum = %f\n", sum);

    return 0;
}
