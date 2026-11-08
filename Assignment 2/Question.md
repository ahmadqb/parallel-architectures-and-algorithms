# Assignment 2

Develop a parallel program to find the maximum element in an array of integers.
Broadcast the array to all processes. Each process finds the maximum element in its
portion, then uses MPI_Send to send its local max to process 0. Process 0 receives all
values and then finds the global max.
