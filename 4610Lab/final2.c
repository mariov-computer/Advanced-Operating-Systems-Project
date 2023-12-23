#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

void parallelSieve(int n, int world_rank, int world_size) {
    int *marked;
    int i, j;

    marked = (int *)malloc((n + 1) * sizeof(int));
    for (i = 2; i <= n; i++) {
        marked[i] = 0;
    }

    double start_time = MPI_Wtime();

    for (i = 2; i * i <= n; i++) {
        if (!marked[i]) {
            for (j = i * i; j <= n; j += i) {
                marked[j] = 1;
            }
        }
    }

    double end_time = MPI_Wtime();

    // Print prime numbers
    if (world_rank == 0) {
        printf("Prime numbers up to %d are:\n", n);
        for (i = 2; i <= n; i++) {
            if (!marked[i]) {
                printf("%d ", i);
            }
        }
        printf("\nThe program took %f seconds to run.\n", end_time - start_time);
    }

    free(marked);
}

int main(int argc, char **argv) {
    int n, process_count;
    int world_rank, world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc != 3) {
        if (world_rank == 0) {
            printf("Usage: mpirun -np <number of processes> ./mpi_sieve <search_max> <process_count>\n");
        }
        MPI_Finalize();
        return 1;
    }

    n = atoi(argv[1]);
    process_count = atoi(argv[2]);

    // Broadcast the values of n and process_count to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&process_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process performs the parallel sieve
    parallelSieve(n, world_rank, world_size);

    MPI_Finalize();
    return 0;
}


