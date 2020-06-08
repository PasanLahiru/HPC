#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]) {
	
	MPI_Init(&argc, &argv);

	int N = 840;
	int npes;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if (myrank == 0) {
		int q = N / npes;
		int start = ((q * myrank) + 1);
		int end = (q * (myrank + 1));
		cout << "\nP" << myrank << " calculate from " << start << " to " << end;

		float sum = 0.0;
		for (int i = start; i <= end; i++) {
			sum = sum + (1 / (1 + (pow(((i - 0.5) / N), 2))));
		}
		//cout << "\nP" << myrank << " sum is : " << sum;

		float n;
		for (int j = 1; j < npes; j++) {
			MPI_Recv(&n, 1, MPI_FLOAT, j, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum = sum + n;
			//cout << "\nP" << myrank << " receive sum" << j << " : " << n;
		}
		cout << "\n\nFinal sum is : " << sum ;
		float pi = 4*(sum/N);
		cout << "\nApproximate value of 'PI' is : " << pi;
	}
	else {
		
		int q = N / npes;
		int start = ((q * myrank) + 1);
		int end = (q * (myrank + 1));
		cout << "\nP" << myrank << " calculate from " << start << " to " << end;

		float sum = 0.0;
		for (int i = start; i <= end; i++) {
			sum = sum + (1 / (1 + (pow(((i - 0.5) / N), 2))));
		}

		MPI_Send(&sum, 1, MPI_FLOAT, 0,myrank, MPI_COMM_WORLD);
		//cout << "\nP" << myrank << " send sum" << myrank << " : " << sum;
	}
	
	MPI_Finalize();

}