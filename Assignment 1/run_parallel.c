//mpicc -g -Wall -o run_parallel run_parallel.c
//mpiexec -n 4 ./run_parallel
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define ARRAY_SIZE 100000000  // Size of the array

int parallelSum(int *array, int size, int rank, int num_procs) {
    int local_sum = 0;
    int global_sum = 0;

    // Calculate local sum
    int chunk_size = size / num_procs;
    int start = rank * chunk_size;
    int end = (rank == num_procs - 1) ? size : (rank + 1) * chunk_size;
    for (int i = start; i < end; i++) {
        local_sum += array[i];
    }

    // Reduce local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return global_sum;
}

int main(int argc, char *argv[]) {
    int rank, num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Allocate memory for the array
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;  // Random value between 0 and 99
    }

    // Perform sum calculation in parallel
    double start_time = MPI_Wtime();
    int parallelResult = parallelSum(array, ARRAY_SIZE, rank, num_procs);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Parallel sum: %d\n", parallelResult);
        printf("Parallel execution time: %.6f seconds\n", end_time - start_time);
    }

    // Free allocated memory
    free(array);

    MPI_Finalize();

    return 0;
}
