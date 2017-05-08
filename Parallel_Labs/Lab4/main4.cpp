#include <stdio.h>
#include <omp.h>

int main()
{
	int cnt = 0;

#pragma omp parallel
	{
#pragma omp atomic
		cnt++;		
	}	

	printf("Count of threads = %d\n", cnt);

	return 0;
}