#include <stdio.h>
#include <omp.h>

#define MAXN 12

int main()
{
	int i, n;

#pragma omp parallel private(i, n)
	{
		n = omp_get_thread_num();

#pragma omp for ordered
		for (i = 0; i < MAXN; i++)
		{
#pragma omp ordered
			{
				printf("Thread #%d, iteration #%d\n", n, i);
			}
		}
	}		

	return 0;
}