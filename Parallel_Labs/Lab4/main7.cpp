#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define _USE_MATH_DEFINES

double simps(double a, double b, int n, double function(double))
{
	double h = (b - a) / (2 * n);

	int k;
	double s1 = 0, s2 = 0;
	double temp;

#pragma omp parallel for shared(a, h) private(k, temp) reduction(+: s1) reduction(+: s2)
	for (k = 1; k < n; k++)
	{
		temp = a + (2 * k - 1) * h;
		s1 += function(temp);
		s2 += function(temp + h);
	}

	s1 += function(b - h);

	return h * (function(a) + function(b) + 4.0 * s1 + 2.0 * s2) / 3.0;
}

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