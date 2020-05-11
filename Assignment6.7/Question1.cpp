#include <mpi.h> 
#include <iostream>
using namespace std;


int main(int argc, char* argv[]) {
	
	MPI_Init(&argc, &argv);
	
	int npes;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	//cout << "\n No Of Processes " <<npes;
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank != 0) {
		
		MPI_Send(&myrank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		//cout << "\nProcess send " << myrank;
	}
	else {
		
		int factorial = 1;
		for (int i = 1; i < npes; i++) {
			int n;
			MPI_Recv(&n, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			factorial = factorial * (n);
		}
		
		cout << "\nFactorial of " << npes-1 << " is : " << factorial << '\n';
		
	}
	
	MPI_Finalize();

}
