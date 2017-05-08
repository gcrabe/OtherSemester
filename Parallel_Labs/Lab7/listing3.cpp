#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	double a = 0, b = 0, c = 0;
	
	MPI_Request Req[4];
	MPI_Status St[4];
	
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	int Posl = (Rank + 1) % Size; 
	int Pred = Rank ? Rank - 1 : Size - 1;
	
	a=Rank + 0.7;
	
	MPI_Isend(&a, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &Req[0]);
	MPI_Irecv(&b, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &Req[1]);
	MPI_Isend(&a, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &Req[2]);
	MPI_Irecv(&c, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &Req[3]);
	
	MPI_Waitall(4, Req, St);
	
	std::cout << "Process " << Rank << " a=" << a << " b=" << b << " c=" << c << std::endl;
	
	MPI_Finalize();

	return 0;
}