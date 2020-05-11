#include <mpi.h> 
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	
	MPI_Init(&argc, &argv);
	
	int npes;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		if (npes == 1) {
			cout << "\nFactorial of " << npes - 1 << " is : " << "1" << '\n';
		}
		else {
			int val = 1;
			MPI_Send(&val, 1, MPI_INT, (myrank + 1), (myrank + 1), MPI_COMM_WORLD);
			//cout <<'\n'<< myrank << " send : " << val;
			int n;
			MPI_Recv(&n, 1, MPI_INT, (npes - 1), npes, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//cout << '\n' << myrank << " receive : " << n;

			cout << "\nFactorial of " << npes - 1 << " is : " << n << '\n';
		}
		
	}
	else {
		int pre_val;
		MPI_Recv(&pre_val, 1, MPI_INT, (myrank - 1), myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//cout << '\n' << myrank << " receive : " << pre_val;
		int factorial = pre_val * myrank;

		if (npes - 1 == myrank) {
			MPI_Send(&factorial, 1, MPI_INT, 0, myrank+1, MPI_COMM_WORLD);
			//cout << '\n' << myrank << " send : " << factorial;
		}
		else {
			MPI_Send(&factorial, 1, MPI_INT, myrank + 1, myrank + 1, MPI_COMM_WORLD);
			//cout << '\n' << myrank << " send : " << factorial;
		}
		
	}
	
	MPI_Finalize();

}