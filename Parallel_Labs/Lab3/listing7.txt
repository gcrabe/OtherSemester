#include <windows.h>
#include <stdio.h>
#include <omp.h>

int main()
{
	int n;

#pragma omp parallel num_threads(3)
	{
#pragma omp sections lastprivate(n)
		{
#pragma omp section
			{
				n = 1;
			}
#pragma omp section
			{
				n = 2;
			}
#pragma omp section
			{
				n = 3;
			}
		}

		printf("Value of n in thread #%d = %d\n", omp_get_thread_num(), n);
	}

	printf("Value of n in serial region = %d\n", n);

	return 0;
}