#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double *aptr = NULL, *bptr = NULL;

#define A(i, j) aptr[N * ((j) - 1) + (i) - 1]
#define B(i) bptr[(i) - 1]

extern "C" void DPOSV(char *uplo, int *n, int *nrhs, double *a, int *lda, double *b, int *ldb, int *info);

void testFunction(int N)
{
	aptr = new double[N * N];
	bptr = new double[N];
	
	int *ipiv = new int[N];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			double DI = i - j;
			A(i, j) = 1.0 / (1.0 + 10.0 * DI * DI);
		}

		B(i) = 1 + 1 / (i * i);
	}

	char uplo = 'U';
	int nrhs = 1;
	int info;

	double timeStart = clock();

	DPOSV(&uplo, &N, &nrhs, aptr, &N, bptr, &N, &info);
	
	printf("time = %.2lf\ninfo = %d\n", (clock() - timeStart) / CLOCKS_PER_SEC, info);

	delete[] ipiv;
	delete[] bptr;
	delete[] aptr;
}

int main(void)
{
	for (int N = 1024; N <= 4096; N *= 2)
		testFunction(N);

	system("PAUSE");
}