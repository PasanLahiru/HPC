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
		int b = 2;
		MPI_Send(&a, 10, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&b, 10, MPI_INT, 1, 2, MPI_COMM_WORLD);
		
		cout << "\nProcess 0 sent a :" << a;
		cout << "\nProcess 0 sent b : " << b << '\n';

	}

	else if (myrank == 1) {
		int a;
		int b;
		MPI_Recv(&b, 10, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&a, 10, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		cout << "\nProcess 1 received a : " << a;
		cout << "\nProcess 1 received b : " << b << '\n';
	}

	MPI_Finalize();

	// when executing this program a "Debug error" window appears. After Ignoring the messages twice program gives the output.
	//Debug error1 tells :- Run-Time Check Failure #2 - Stack around the variable 'myrank' was corrupted.
	//Screen captures of the errors are included here.
}