#include <mpi.h>
#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv)
{
	MPI_Init(NULL,NULL);
	
	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	
	if (Size >= 2)
	{
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
		
		if (Rank == 0)
		{
			int N = 3 + (rand() % 10);
			double *A=new double[N];
			
			for (int k = 0; k < N; k++)
				A[k]=k + 0.7;
			
			std::cout << "Process 1 sends the data:" << std::endl;
			
			for(int k = 0; k < N; k++)
				std::cout << A[k] << std::endl;
			
			MPI_Send(A, N, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
			
			delete[] A;
		}

		if(Rank==1){
			MPI_Status St;
			MPI_Probe(0, 5, MPI_COMM_WORLD, &St);
			
			int N;
			MPI_Get_count(&St, MPI_DOUBLE, &N);
			
			double *A=new double[N];
			MPI_Recv(A, N, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &St);
			
			std::cout << "Process 1 has accepted the data:" << std::endl;
			
			for(int k=0; k<N; k++)
				std::cout << A[k] << std::endl;
			
			delete[] A;
		}
	}
	else
	{
		std::cout <<"Performance of the program not less than in 2 processes is required" << std::endl;
	}

	MPI_Finalize();
	
	return 0;
}