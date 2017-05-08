#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAXN 15

void myTask(int k)
{
#ifdef _OPENMP
	int n = omp_get_thread_num();
#else
	int n = 0;
#endif
    
	printf("k = %d Thread #%d started calculating\n", k, n);	
	Sleep(1000 * (((k + 6) % 7) + ((k + 3) % 4)));
	printf("k = %d Thread #%d completed calculating\n", k, n);
}

int main()
{
	double timeStart = clock();

#pragma omp parallel
	{
#pragma omp single
		{
			for (int k = 0; k < MAXN; k++)
			{
#pragma omp task
				myTask(k);
			}
#pragma omp taskwait
		}
	}

	puts("Tasks completed");
	printf("Time = %lf sec\n", (clock() - timeStart) / CLOCKS_PER_SEC);
	
	return 0;
}
