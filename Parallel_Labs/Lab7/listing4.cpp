#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	double a = 0, b = 0, c = 0;
	
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	int Posl = (Rank + 1) % Size; 
	int Pred = Rank ? Rank - 1 : Size - 1; 
	
	a = Rank + 0.7;
	
	MPI_Status St;
	MPI_Sendrecv(&a, 1, MPI_DOUBLE, Posl, 5, &b, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &St);
	MPI_Sendrecv(&a, 1, MPI_DOUBLE, Pred, 5, &c, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &St);
	
	std::cout << "Process " << Rank << " a=" << a << " b=" << b << " c=" << c << std::endl;
	
	MPI_Finalize();
	
	return 0;
}