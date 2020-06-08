#include <mpi.h> 
#include<time.h>
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char** argv) {

	const int source = 0; // Select a source here
	const int n = 4;
	int A[n][n];
	
	srand(time(NULL)); // initialize random seed

	MPI_Init(NULL, NULL);

	int npes;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				A[r][c] = rand() % 100 + 1;
				printf("%d ",A[r][c]);
			}
			printf("\n");
		}
	}
	//Broadast method shold be called by all the processes
	MPI_Bcast(A, n * n, MPI_INT, source, MPI_COMM_WORLD);

	
	int cmin = 10000;
	for (int i = 0; i < n; i++) {
		if (A[i][rank] < cmin) {
			cmin = A[i][rank];
		}
	}
	printf("Minimum of column %d = %d.\n", rank, cmin);
	
	int minimum;
	MPI_Reduce(&cmin, &minimum, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Smallest value = %d.\n", minimum);
	}
	
	MPI_Finalize();

}