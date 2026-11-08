// gcc -o run_serial run_serial.c
//./run_serial
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000000 // Size of the array

int sequentialSum(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    // Allocate memory for the array
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;  // Random value between 0 and 99
    }

    // Perform sum calculation sequentially
    clock_t start = clock();
    int sequentialResult = sequentialSum(array, ARRAY_SIZE);
    clock_t end = clock();

    double sequentialTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sequential sum: %d\n", sequentialResult);
    printf("Sequential execution time: %.6f seconds\n", sequentialTime);

    // Free allocated memory
    free(array);

    return 0;
}
