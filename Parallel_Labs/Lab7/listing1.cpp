#include "mpi.h"
#include <iostream>

const int NMAX = 9000000;
const int NTIMES = 10;

double a[NMAX];

int main(int argc, char **argv)
{
	double _2_d20=pow(2.0,20);
	int n = 0, lmax = 0;
	double max = 0.0;
	
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	while (n <= NMAX) 
	{
		double time_start = MPI_Wtime();
		for (int i=0; i<NTIMES; i++){
			if (Rank == 0)
			{
				MPI_Status St;
				MPI_Send(a, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
				MPI_Recv(a, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &St);
			}

			if (Rank == 1)
			{
				MPI_Status St;
				MPI_Recv(a, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &St);
				MPI_Send(a, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
			}
		}

		double time = (MPI_Wtime() - time_start) / (2 * NTIMES);
		double bandwidth = (8.0 * n / _2_d20) / time;
		
		if (max < bandwidth)
		{
			max = bandwidth;
			lmax = 8*n;
		}

		if (Rank == 0)
		{
			if (n == 0)
				std::cout << "latency: " << time << " s" << std::endl;
			else
				std::cout << 8 * n << " bytes" << " bandwidth " << bandwidth << "MB/s" << std::endl;
		}

		if (n == 0)
			n = 1;
		else 
			n *= 2;
	}

	if (Rank==0)
	{
		std::cout << "max bandwidth " << max << " MB/s length " << lmax << " bytes" << std::endl;
	}
	
	MPI_Finalize();
	
	return 0;
}