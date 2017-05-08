#include "mpi.h"
#include <iostream>
#include <cmath>

const int N = 1000;

double Get_A(int m, int n)
{
	double Tmp = n - m;
	Tmp *= Tmp;
	
	double S = (sin(1.0 * m) + cos(1.0 * m)) / (Tmp + 1);
	
	for (int k = 2; k <= N; k++)
		S += (sin(1.0 * m) + cos(m - 2.0 * k)) / (Tmp + k * k);
	
	return S;
}

int main(int argc, char **argv)
{
	MPI_Init(NULL, NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	if (Size < 2)
	{
		std::cout << "It is required not less than two processes!" << std::endl;
	}
	else
	{
		int N_S = N / (Size - 1);
		int n_s = N % (Size - 1);

		if (Rank == 0)
		{
			double *A = new double[N * N];
			double *B = new double[N * N];
			
			MPI_Request *Req = new MPI_Request[Size - 1];
			
			double Tms = MPI_Wtime();
			
			for (int k = 1; k < Size; k++)
				MPI_Irecv(&A[N_S * N * (k - 1)], N_S*N, MPI_DOUBLE, k, 5, MPI_COMM_WORLD, &Req[k - 1]);
			
			for (int k = 0; k < Size - 1; k++)
			{
				int Idx;
				MPI_Status St;
				MPI_Waitany(Size - 1, Req, &Idx, &St);
				
				for (int k = N_S * Idx; k < N_S * (Idx + 1); k++)
					for (int j = 0; j < N; j++)
						B[N * k + j] = A[N * j + k];
			}

			for (int k = N_S * (Size - 1); k < N; k++)
				for (int j = 0; j < N; j++)
				{
					A[N * k + j] = Get_A(k + 1,j + 1);
					B[N * j + k] = A[N * k + j];
				}

			Tms = MPI_Wtime() - Tms;
			std::cout << "Time=" << Tms << " s" << std::endl;
			
			delete[] Req;
			delete[] B;
			delete[] A;
		 }
		 else
		 {
			 double *A = new double[N_S * N];
			 
			 for (int k = 0; k < N_S; k++)
				for (int j=0; j<N; j++)
					A[N_S * k + j] = Get_A(1 + N_S * (Rank - 1) + k, j + 1);
			 
			 MPI_Send(A, N_S*N, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
			 delete[] A;
		 }
	}

	MPI_Finalize();
	
	return 0;
}