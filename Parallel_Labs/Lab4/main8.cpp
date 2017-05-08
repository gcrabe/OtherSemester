#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAXN 1024

int a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN];

int main()
{
	int i, j, k;
    double time_start;

    for (i = 0; i < MAXN; i++)
    	for (j = 0; j < MAXN; j++)
    		a[i][j] = b[i][j] = i * j;

   	time_start = clock();

#pragma omp parallel for shared(a, b, c) private(i, j, k)
	for (i = 0; i < MAXN; i++)
	{
		for (j = 0; j < MAXN; j++)
		{
			c[i][j] = 0.0;

			for (k = 0; k < MAXN; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	time_start = (clock() - time_start) / CLOCKS_PER_SEC;

	printf("time = %.2lf\n", time_start);

	return 0;
}