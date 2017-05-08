#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	if (Size >= 3)
	{
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
		
		if (Rank == 1)
		{
			double DVal = 7.7;
			MPI_Send(&DVal, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
		}

		if (Rank == 2)
		{
			int IVal=3;
			MPI_Send(&IVal, 1, MPI_INTEGER, 0, 6, MPI_COMM_WORLD);
		}

		if (Rank==0)
		{
			double DVal=0;
			int IVal=0;
			
			MPI_Status St;
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);
			
			if (St.MPI_TAG == 5)
			{
				MPI_Recv(&DVal, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				std::cout << "Process 0 has received from process " << St.MPI_SOURCE << " DVal=" << DVal << std::endl;
			}

			if (St.MPI_TAG == 6)
			{
				MPI_Recv(&IVal, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				std::cout << "Process 0 has received from process " << St.MPI_SOURCE << " IVal=" << IVal << std::endl;
			}

			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);
			
			if (St.MPI_TAG == 5)
			{
				MPI_Recv(&DVal, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				std::cout << "Process 0 has received from process " << St.MPI_SOURCE << " DVal=" << DVal << std::endl;
			}

			if (St.MPI_TAG == 6)
			{
				MPI_Recv(&IVal, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				std::cout << "Process 0 has received from process " << St.MPI_SOURCE << " IVal=" << IVal << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Требуется выполнение программы не менее чем в 3-х процессах" << std::endl;
	}

	MPI_Finalize();
	
	return 0;
}
