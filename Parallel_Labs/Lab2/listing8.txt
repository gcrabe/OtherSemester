#include <stdio.h>
#include <omp.h>

#define NMAX 8

int main()
{
	int n = 1;

	printf("Value of n (start) = %d\n", n);

#pragma omp parallel num_threads(4) firstprivate(n)
	{
		printf("Value of n in thread (start) = %d\n", n);
		n = omp_get_thread_num();
		printf("Value of n in thread (end) = %d\n", n);
	}

	printf("Value of n (end) = %d\n", n);

	return 0;
}