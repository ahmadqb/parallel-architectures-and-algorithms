# Parallel Architectures and Parallel Algorithms (CE 502)

Homework assignments from the graduate course **CE 502: Parallel Architectures and Parallel Algorithms**, completed between April and June 2025.

The course introduces parallel computing: how parallel hardware is organized, how parallel algorithms are designed, and how to program and measure them on shared-memory, message-passing and GPU platforms.

## Course topics

- Introduction to parallel computing and parallel programming platforms
- Parallelism in processors, multi-core processors, and classification of parallel architectures
- Principles of parallel algorithm design, data dependencies, load balancing
- Basic communication operations
- Analytical modeling of parallel program performance (speedup, efficiency)
- Message-passing programming (MPI)
- Shared-address-space programming (pthreads, OpenMP)
- GPU programming with CUDA
- Dense matrix algorithms

**Textbook:** Grama, Karypis, Kumar, Gupta, *Introduction to Parallel Computing*, 2nd Edition, 2003.

## Assignments

| # | Folder | Date | Topics |
|:-:|--------|:----:|--------|
| 1 | [`assignment1`](./assignment1) | Apr 2025 | Pipelining, cache hit/miss behaviour, memory hierarchy timing, measuring speedup and efficiency |
| 2 | [`assignment2`](./assignment2) | May 2025 | Message passing with MPI (e.g. broadcast, send/receive, global maximum) |
| 3 | [`assignment3`](./assignment3) | May 2025 | Shared-memory programming with pthreads (e.g. parallel binary search) |
| 4 | [`assignment4`](./assignment4) | Jun 2025 | OpenMP matrix multiplication and a serial vs. parallel performance comparison |

<!-- Check that rows 2 and 3 match what is actually in those folders and adjust the topics if needed. -->

## Highlights

- **Assignment 1** works through the analytical side of the course: how long floating-point additions take with and without pipelining, how cache levels change the cost, and how to compute speedup and efficiency from measured runs.
- **Assignment 4** compares serial and OpenMP matrix multiplication with 4 threads. The speedup was about 2.2× for 100×100, 3.75× for 500×500 and 3.0× for 1000×1000. Thread overhead limits small sizes and memory bandwidth limits large ones.

## Tools

- C
- MPI (`mpicc`, `mpirun`)
- POSIX threads (`-lpthread`)
- OpenMP (`-fopenmp`)

## Repository layout

```
.
├── README.md
├── Assignment1/
├── Assignment2/
├── Assignment3/
└── Assignment4/
```


## Note

These are my solutions to coursework for CE 502, kept here as a record of what I learned.
