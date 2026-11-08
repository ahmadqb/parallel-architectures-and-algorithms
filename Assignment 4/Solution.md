# Assignment 4 – OpenMP Matrix Multiplication

**Course:** Parallel Architectures and Parallel Algorithms

---

## Question 1: OpenMP Matrix Multiplication (5 marks)

**Task:** Initialize two matrices with predefined values, multiply them using OpenMP, and print the result.

### Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 3  // Dimension of the square matrices

int main() {
    int i, j, k;
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B with predefined values
    int initA[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int initB[N][N] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    // Copy initial values into A and B, and zero the result matrix C
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = initA[i][j];
            B[i][j] = initB[i][j];
            C[i][j] = 0;
        }
    }

    // Perform C = A x B, parallelizing the outer loop with OpenMP
    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int sum = 0;
            for (k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    // Print the resulting matrix C
    printf("Resulting matrix C (A x B):\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

### Compile and run

```bash
gcc -fopenmp -o matmul matmul.c
./matmul
```

### Expected output

```
Resulting matrix C (A x B):
30      24      18
84      69      54
138     114     90
```

### Explanation

- `#pragma omp parallel for` splits the iterations of the outer `i` loop (the rows of `C`) among the threads.
- `i`, `j` and `k` are `private`, so each thread has its own loop counters. `A`, `B` and `C` are `shared`.
- No two threads write to the same element of `C`, because each thread computes whole rows. No locks or critical sections are needed.

---

## Question 2: Serial vs. Parallel Performance (5 marks)

### Serial version

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // for clock()

#define N 500  // Change at compile time (e.g. -DN=1000)

int main() {
    int i, j, k;
    double **A, **B, **C;
    clock_t start, end;
    double cpu_time;

    // Allocate A, B, C
    A = (double**)malloc(N * sizeof(double*));
    B = (double**)malloc(N * sizeof(double*));
    C = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        A[i] = (double*)malloc(N * sizeof(double));
        B[i] = (double*)malloc(N * sizeof(double));
        C[i] = (double*)malloc(N * sizeof(double));
    }

    // Initialization: A[i][j] = i + j, B[i][j] = i - j
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (double)(i + j);
            B[i][j] = (double)(i - j);
            C[i][j] = 0.0;
        }
    }

    // Serial matrix multiplication: C = A x B
    start = clock();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            double sum = 0.0;
            for (k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    end = clock();

    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[SERIAL] N = %d, elapsed = %f seconds\n", N, cpu_time);

    // Print a few elements to verify correctness
    printf("C[0][0] = %f, C[N-1][N-1] = %f\n", C[0][0], C[N-1][N-1]);

    // Free memory
    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
```

### Parallel version (modified for different matrix sizes)

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500  // Change at compile time (e.g. -DN=1000)

int main() {
    int i, j, k;
    double **A, **B, **C;
    double t_start, t_end;

    // Allocate A, B, C
    A = (double**)malloc(N * sizeof(double*));
    B = (double**)malloc(N * sizeof(double*));
    C = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        A[i] = (double*)malloc(N * sizeof(double));
        B[i] = (double*)malloc(N * sizeof(double));
        C[i] = (double*)malloc(N * sizeof(double));
    }

    // Same initialization as the serial version
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (double)(i + j);
            B[i][j] = (double)(i - j);
            C[i][j] = 0.0;
        }
    }

    // Parallel matrix multiplication
    omp_set_num_threads(4);  // number of threads used in the experiments
    t_start = omp_get_wtime();

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            double sum = 0.0;
            for (k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    t_end = omp_get_wtime();
    printf("[OPENMP]  N = %d, threads = %d, elapsed = %f seconds\n",
           N, omp_get_max_threads(), t_end - t_start);

    // Free memory
    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
```

### Compile and run

```bash
# Serial
gcc -O2 -DN=1000 -o serial serial.c
./serial

# Parallel (4 threads)
gcc -O2 -fopenmp -DN=1000 -o parallel parallel.c
./parallel
```

Change `-DN=` to 100, 500 or 1000 for each matrix size.

### Results (4 threads)

Speedup = T<sub>serial</sub> / T<sub>parallel</sub>.

| Matrix size (N×N) | Serial time (s) | Parallel time (s), 4 threads | Speedup (×) |
|:-----------------:|----------------:|-----------------------------:|:-----------:|
| 100  | 0.001358 | 0.000628 | 2.16 |
| 500  | 0.183302 | 0.048817 | 3.75 |
| 1000 | 1.702120 | 0.563994 | 3.02 |

### Discussion

**Small matrix (100×100): speedup ≈ 2.16×**
Even this small matrix gets a clear improvement. The fixed costs of OpenMP (forking threads, scheduling loop iterations, synchronizing at the end) are a larger share of the total runtime here. Four threads therefore don't reach the ideal 4× speedup.

**Medium matrix (500×500): speedup ≈ 3.75×**
The workload per thread is now large enough to hide the thread overhead. Each thread handles about 125 rows, so all cores stay busy with little idle time. This is the sweet spot where the computation dominates the synchronization cost, and the speedup comes close to the ideal 4×.

**Large matrix (1000×1000): speedup ≈ 3.02×**
The computation clearly dominates, but memory behaviour starts to limit scaling. A 1000×1000 matrix of `double` is about 8 MB, which doesn't fit in the L2 cache (and may not fit in L3). All four threads read the columns of `B` (a strided access pattern) from main memory at the same time. The resulting contention and cache misses reduce efficiency, giving about 3× instead of 4×.

### Summary

| Matrix size | Speedup | Efficiency (speedup / 4 threads) | Limiting factor |
|:-----------:|:-------:|:--------------------------------:|-----------------|
| 100  | 2.16× | 54% | Thread-management overhead |
| 500  | 3.75× | 94% | Close to ideal, compute-bound |
| 1000 | 3.02× | 76% | Memory bandwidth and cache misses |

Parallelizing the outer loop with OpenMP gives a large speedup for all three sizes. The benefit is largest for medium-sized matrices. For very small matrices thread overhead limits it, and for large matrices memory bandwidth does.

> **Note:** Times come from a single run on a 4-thread setup. The serial version is timed with `clock()` (CPU time) and the parallel version with `omp_get_wtime()` (wall-clock time). Averaging several runs would give more stable numbers.
