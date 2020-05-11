#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int val1 = 3;
		int val2 = 5;
		int sum1;
		MPI_Send(&val1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&val2, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		MPI_Recv(&sum1, 1, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << myrank << ":\n \tI\'ve received the sum from Process " << myrank+1 ;
		cout << "\n\tThe sum is equal to " << sum1;
	}

	else if (myrank == 1) {
		int val3;
		int val4;
		int sum;
		MPI_Recv(&val3, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&val4, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << myrank << ":\n \tI\'ve received " << val3 << " and " << val4 << " from Process " << myrank-1;
		sum = val3 + val4;
		cout << "\n\tThe sum of the two received values are " << sum;
		MPI_Send(&sum, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}