#include "mpi.h"
#include <iostream>

const int BufSize=sizeof(double)+MPI_BSEND_OVERHEAD;

int main(int argc, char **argv)
{
	double a = 0, b = 0, c = 0;
	MPI_Init(NULL, NULL);

	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	int Rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	int Posl = (Rank + 1) % Size; 
	int Pred = Rank ? Rank - 1 : Size - 1; 
	
	a = Rank + 0.7;
	void *Buf = malloc(BufSize);
	
	MPI_Buffer_attach(Buf, BufSize);
	MPI_Bsend(&a, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD);
	
	MPI_Status St;
	MPI_Recv(&b, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD, &St);
	
	int Tmp;
	MPI_Buffer_detach(Buf, &Tmp);
	MPI_Buffer_attach(Buf, BufSize);
	
	MPI_Bsend(&a, 1, MPI_DOUBLE, Pred, 5, MPI_COMM_WORLD);
	MPI_Recv(&c, 1, MPI_DOUBLE, Posl, 5, MPI_COMM_WORLD, &St);
	MPI_Buffer_detach(Buf, &Tmp);
	
	if (!Buf) free(Buf);
	
	std::cout << "Process " << Rank << " a=" << a << " b=" << b << " c=" << c << std::endl;
	
	MPI_Finalize();

	return 0;
}