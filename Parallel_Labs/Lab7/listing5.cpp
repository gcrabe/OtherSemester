#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	double a = 0, b = 0, c = 0;
	
	MPI_Request Req[4];
	MPI_Status St[4];
	
	MPI_Init(NULL, NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	int Posl = (Rank + 1) % Size; 
	int Pred = Rank ? Rank - 1 : Size - 1; 
	
	a = Rank + 0.4;
	
	MPI_Send_init(&a, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &Req[0]);
	MPI_Recv_init(&b, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &Req[1]);
	MPI_Send_init(&a, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &Req[2]);
	MPI_Recv_init(&c, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &Req[3]);
	
	for (int k = 1; k <= 3; k++)
	{
		a += 0.1;
		MPI_Startall(4, Req);
		MPI_Waitall(4, Req, St);
	}

	for (int k = 0; k < 4; k++)
		MPI_Request_free(&Req[k]);
	
	std::cout << "Process " << Rank << " a=" << a << " b=" << b << " c=" << c << std::endl;
	
	MPI_Finalize();
	
	return 0;
}