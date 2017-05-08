#include <mpi.h>
#include <iostream>

int main(int argc, char **argv)
{
	MPI_Init(NULL,NULL);

	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

	if (Rank == 0)
	{
		double Val = 7.77;
		int BufSize = sizeof(double) + MPI_BSEND_OVERHEAD;
		void *Buff = malloc(BufSize);
	
		MPI_Buffer_attach(Buff, BufSize);
		MPI_Bsend(&Val, 1, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
		MPI_Buffer_detach(Buff, &BufSize);

		if (!Buff) free(Buff);
		
		std::cout << "Process 0 has sent the data" << std::endl;
	}
	else if (Rank == 1)
	{
		double Val = 0;
		MPI_Status Status;
		MPI_Recv(&Val, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &Status);
		
		std::cout << "Process 1 has accepted the data from process 0. Val=" << Val << std::endl;
	}
	else
	{
		std::cout << "Process " << Rank	<<" does not accept participation in information interchange" << std::endl;
	}

	MPI_Finalize();
	
	return 0;
}