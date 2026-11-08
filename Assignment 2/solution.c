// mpicc max.c -o max
// mpirun -np 4 ./max

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define ARRAY_SIZE 120 // Size of the array

int main(int argc, char *argv[]) {
    int rank, size, i;
    int array[ARRAY_SIZE];
    int local_max, global_max = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank * 100); // Unique seed for each process

    // Generate random numbers on process 0
    if (rank == 0) {
        printf("Array:\n");
        for (i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 100;
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    // Broadcast the array to all processes
    MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Determine portion of the array this process will handle
    int elements_per_process = ARRAY_SIZE / size;
    int start_index = rank * elements_per_process;
    int end_index = (rank == size - 1) ? ARRAY_SIZE : start_index + elements_per_process;

    // Find local maximum
    local_max = array[start_index];
    for (i = start_index + 1; i < end_index; i++) {
        if (array[i] > local_max) {
            local_max = array[i];
        }
    }

    if (rank != 0) {
        // Send local maximum to process 0
        MPI_Send(&local_max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 compares with its own local max
        global_max = local_max;

        // Receive local maxima from other processes and find global max
        int recv_max;
        for (i = 1; i < size; i++) {
            MPI_Recv(&recv_max, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (recv_max > global_max) {
                global_max = recv_max;
            }
        }

        // Print the global maximum
        printf("Global Maximum: %d\n", global_max);
    }

    MPI_Finalize();
    return 0;
}
