#include "mpi.h"
#include <iostream>

int main()
{
	int NProc, ProcId;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &NProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcId);
	
	std::cout << "Total number of processes: " << NProc << " Process identifier: " << ProcId << std::endl;
	
	MPI_Finalize();
	
	return 0;
}