#include "mpi.h"
#include <iostream>

const int N = 8;

void UsrFunc(_In_count_(*len) void *In, _Inout_ void* InOut, _In_ int* len, _In_ MPI_Datatype *Ty)
{
	int *InV = (int *)In;
	int *InOutV = (int *)InOut;

	for (int k = 0; k < (*len); k++)
		InOutV[k] = (InV[k] + InOutV[k]) % 8;
}

int main(int argc, char **argv)
{
	int *A = new int[N];
	MPI_Init(NULL, NULL);
	
	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
	
	for (int k = 0; k < N; k++)
		A[k]=k + Rank;
	
	MPI_Op My_Op;
	MPI_Op_create(&UsrFunc, true, &My_Op);
	
	if (Rank == 0)
	{
		int *B = new int[N];
		
		MPI_Reduce(A, B, N, MPI_INT, My_Op, 0, MPI_COMM_WORLD);
		
		for (int k=0; k<N; k++)
			std::cout << B[k] << " ";
		
		std::cout << std::endl;
		
		delete[] B;
	}
	else
	{
		MPI_Reduce(A, NULL, N, MPI_INT, My_Op, 0, MPI_COMM_WORLD);
	}

	MPI_Op_free(&My_Op);
	MPI_Finalize();
	
	delete[] A;
	
	return 0;
}
