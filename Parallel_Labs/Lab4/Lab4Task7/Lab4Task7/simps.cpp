#include "simps.h"
#include <omp.h>

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