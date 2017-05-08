#include <mpi.h>
#include <iostream>

int main(int argc, char **argv)
{
	double a = 0, b = 0;
	
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	if (Rank == 0)
	{
		a = 7.7;
		MPI_Send(&a, 1, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
		MPI_Status Status;
		MPI_Recv(&b, 1, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &Status);
	}
	if (Rank == 1)
	{
		b = 3.3;
		MPI_Status Status;
		MPI_Recv(&a, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &Status);
		MPI_Send(&b, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
	}

	std::cout << "Process " << Rank << " a=" << a << " b=" << b << std::endl;
	
	MPI_Finalize();
	
	return 0;
}