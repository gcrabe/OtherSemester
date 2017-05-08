#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double *aptr = NULL;
double *bptr = NULL;
double *cptr = NULL;

#define A(i, j) aptr[N * ((j) - 1) + (i) - 1]
#define B(i, j) bptr[N * ((j) - 1) + (i) - 1]

extern "C" void DGEMM(char *transa, char *transb, int *m, int *n, int *k,
							double *alpha, double *a, int *lda, double *b, const int *ldb,  double *beta, double *c, int *ldc);

void testFunction(int N)
{
	aptr = new double[N * N];
	bptr = new double[N * N];
	cptr = new double[N * N];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			A(i, j) = i * j;
			B(i, j) = i * j;
		}
	}

	char transa = 'N', transb = 'N';
	double alpha = 1, beta = 0;

	double timeStart = clock();

	DGEMM(&transa, &transb, &N, &N, &N, &alpha, aptr, &N, bptr, &N, &beta, cptr, &N);

	printf("time = %.2lf\n", (clock() - timeStart) / CLOCKS_PER_SEC);

	delete []cptr;
	delete []bptr;
	delete []aptr;
}

int main(int argc, char **argv)
{
	for (int N = 1024; N <= 4096; N *= 2) {
		testFunction(N);
	}

	system("PAUSE");

	return 0;
}