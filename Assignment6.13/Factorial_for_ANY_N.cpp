#include <mpi.h> 
#include <iostream>
#include <math.h> 
using namespace std;

int calperProcess(int N, int rank, int np) {
	int countPerProcess = ceil(N / np);
	int start = (countPerProcess * rank) + 1;
	int end = countPerProcess * (rank + 1);
	if (rank == np - 1) end = N;

	int val = 1;
	for (int i = start; i <= end; i++) {
		val = val*i;
	}
	return val;
}

int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int np;
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int N = atoi(argv[1]);

	// Calculate part of each processor
	int cal = calperProcess(N, rank, np);

	int factorial;
	MPI_Reduce(&cal, &factorial, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Factorial of %d is %d.\n", N,factorial);
	}

	MPI_Finalize();
}