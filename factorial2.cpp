#include <mpi.h> 
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char** argv) {

	const int source = 0; // Select a source here

	MPI_Init(NULL, NULL);

	int npes;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int num;
	if (rank == 0) {
		cout << "Enter a number less than no.of processes : ";
		cin >> num;
	}

	//Broadast method shold be called by all the processes
	MPI_Bcast(&num, 1, MPI_INT, source, MPI_COMM_WORLD);

	//if (rank == 0) printf("Process 0 has sent %d to all other processes\n", num);
	//else printf("Process %d received data %d from root process\n", rank, num);

	/*int factorial, fact = 1;
	if (rank <= num and rank != 0) {
		fact = rank;
	}*/
	//MPI_Reduce(&fact, &factorial, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	if (num >= npes) {
		printf(" Enter a valid number less than no.of processes.\n");
	}
	else {
		if (rank != 0) {
			int send_val = rank;
			if (rank > num) send_val = 1;
			MPI_Send(&send_val, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		else {
			int f = 1;
			for (int i = 1; i < npes; i++) {
				int n;
				MPI_Recv(&n, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				f = f * n;
			}
			printf("Factorial of %d  = %d.\n", num, f);
		}
	}
	

	/*if (rank == 0) {
		printf("factorial %d is %d.\n", num, factorial);
	}*/
	
	MPI_Finalize();

}