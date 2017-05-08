#include <windows.h>
#include <stdio.h>
#include <omp.h>

int main()
{
	int n;

#pragma omp parallel num_threads(3) private(n)
	{
		n = omp_get_thread_num();

#pragma omp sections
		{
#pragma omp section
			{
				printf("1st section, thread #%d\n", n);
			}
#pragma omp section 
			{
				printf("2nd section, thread #%d\n", n);
			}
#pragma omp section
			{
				printf("3rd section, thread #%d\n", n);
			}
#pragma omp section
			{
				printf("4th section, thread #%d\n", n);
			}
#pragma omp section 
			{
				printf("5th section, thread #%d\n", n);
			}
		}
		
		printf("Parallel region, thread #%d\n", n);
	}

	return 0;
}