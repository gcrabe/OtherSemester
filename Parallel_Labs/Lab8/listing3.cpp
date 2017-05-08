#include "mpi.h"
#include <iostream>
#include <math.h>
#include <time.h>

#define M_PI 3.14153265358979

double MPI_Simps(double a, double b, int N, double Func(double), int & ProcID)
{
	double h = (b - a) / (2 * N);
	int k, NumProc;
	double S1, mpi_S1, S2, mpi_S2, Tmp;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &NumProc);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcID);
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	mpi_S1=0;
	mpi_S2=0;
	
	for (k = 1 + ProcID; k < N; k += NumProc)
	{
		Tmp = a + (2 * k - 1) * h;
		mpi_S1 += Func(Tmp);
		mpi_S2 += Func(Tmp + h);
	}

	MPI_Reduce(&mpi_S1, &S1, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mpi_S2, &S2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	MPI_Finalize();
	
	S1 += Func(b - h);

	return h * (Func(a) + Func(b) + 4.0 * S1 + 2.0 * S2) / 3.0;
}

double My_F(double x)
{
	return 1.0 / (1.0 + x * x);
}

int main(void)
{
	int ProcID;
	double Tms = clock();
	double Intgr = MPI_Simps(0, 1000000, 1000000000, My_F, ProcID);
	
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;

	if (ProcID == 0)
	{
		std::cout << "Time=" << Tms << " sec" << std::endl;
		std::cout.precision(8);
		std::cout << "Intgr=" << Intgr << " " << M_PI / 2.0 << std::endl;
	}

	return 0;
}