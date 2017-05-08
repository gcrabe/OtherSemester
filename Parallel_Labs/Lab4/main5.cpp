#include <stdio.h>
#include <omp.h>
#include <windows.h>

omp_lock_t lock;

int main()
{
	int n;
	omp_init_lock(&lock);

#pragma omp parallel num_threads(4) private(n)
	{
		n = omp_get_thread_num();

		omp_set_lock(&lock);
  		
  		printf("The beginning of the closed section, thread #%d\n", n);
  		Sleep((2 + 3 * ((n + 1) % 2)) * 1000);
  		printf("The end os the closed section, thread #%d\n", n);
  		
  		omp_unset_lock(&lock);
  	}

  	omp_destroy_lock(&lock);

	return 0;
}