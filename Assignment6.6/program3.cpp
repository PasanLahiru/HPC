#include <mpi.h> 
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int a = 1;
		int b;
		MPI_Ssend(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&b, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "\nProcess 0 sent a :" << a;
		cout << "\nProcess 0 received b : " << b << '\n';

	}

	else if (myrank == 1) {
		int a = 2;
		int b;
		MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Ssend(&a, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		
		cout << "\nProcess 1 sent a : " << a;
		cout << "\nProcess 1 received b : " << b << '\n';
	}

	MPI_Finalize();

	//This program gives the output. Infinite waiting does not happens. MPI Ssend works as buffered message passing operation.
	// Deadlock does not appear.
}