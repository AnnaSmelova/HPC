#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	const long N = 1<<30;
	double x, y, pi, start, end;
	int i, tid, cnt = 0;

	start = omp_get_wtime();
	#pragma omp parallel private(i,x,y,tid)
	{
		tid = omp_get_thread_num();
        unsigned int seed = tid * N;
		#pragma omp for reduction(+:cnt)
		for (i = 0; i < N; i++) 
		{
            x = (double)rand_r(&seed)/(double)(RAND_MAX);
			y = (double)rand_r(&seed)/(double)(RAND_MAX);

			if ((x * x + y * y) <= 1)
				cnt += 1;
		}
	}
	end = omp_get_wtime();
	pi = 4 * (double)(cnt) / (double)N;

    printf("Threads: %d, Iterations: %ld, time: %f seconds\n", omp_get_max_threads(), N, (end-start));

    printf("Pi = %f\n", pi);
	return 0;
}