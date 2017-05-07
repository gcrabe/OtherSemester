#include <stdio.h>
#include <time.h>

#include "simps.h"

#define M_PI 3.14159265358979

double my_function(double x)
{
	return 1.0 / (1.0 + x * x);
}

int main()
{
	double time_start = clock();

	double res = simps(0, 1e6, (int) 1e9, my_function);

	time_start = (clock() - time_start) / CLOCKS_PER_SEC;

	printf("time = %.2lf\nres = %.8lf %.8lf\n", time_start, res, M_PI / 2.0);

	return 0;
}