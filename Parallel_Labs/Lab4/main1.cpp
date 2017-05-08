#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel num_threads(2)
	{
		puts("Message #1");
		puts("Message #2");
		puts("Message #3");
#pragma omp barrier
		puts("Message #4");
	}

	return 0;
}