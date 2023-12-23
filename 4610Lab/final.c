#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) {
            printf("Usage: %s <search_max> <process_count>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int search_max = strtol(argv[1], NULL, 10);
    int sqrt_search_max = (int)sqrt(search_max);
    int process_count = strtol(argv[2], NULL, 10);

    //new line


    //end

    int range = (search_max - 2 + size) / size;
    int start = 2 + rank * range;
    int end = start + range;
    if (end > search_max) {
        end = search_max;
    }

    int* local_primes = (int*)malloc((end - start) * sizeof(int));
    if (local_primes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        MPI_Finalize();
        return 1;
    }

    for (int i = 0; i < end - start; i++) {
        local_primes[i] = start + i;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double time_start, time_end;
    if (rank == 0) {
        time_start = MPI_Wtime();
    }

    for (int i = 2; i <= sqrt_search_max; i++) {
        if (i >= start && i < end) {
            for (int j = i * i; j <= search_max; j += i) {
                if (j >= start && j < end) {
                    local_primes[j - start] = 0;
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Gather the local prime arrays to the root process
int* all_primes = NULL;
int* counts = NULL;
int* displs = NULL;

if (rank == 0) {
    all_primes = (int*)malloc(search_max * sizeof(int));
    counts = (int*)malloc(size * sizeof(int));
    displs = (int*)malloc(size * sizeof(int));
}

// Gather the count of primes from each process to the root process
MPI_Gather(&range, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

// Calculate displacements for gathering
if (rank == 0) {
    displs[0] = 0;
    for (int i = 1; i < size; i++) {
        displs[i] = displs[i - 1] + counts[i - 1];
    }
}

// Gather the local prime arrays to the root process
MPI_Gatherv(local_primes, range, MPI_INT, all_primes, counts, displs, MPI_INT, 0, MPI_COMM_WORLD);

// Print or save the prime numbers if needed
if (rank == 0) {
    printf("The prime numbers are: ");
    for (int i = 0; i < search_max; i++) {
        if (all_primes[i] != 0) {
            printf("%d ", all_primes[i]);
        }
    }
    printf("\n");

    // Deallocate memory to avoid memory leaks
    free(all_primes);
    free(counts);
    free(displs);

    time_end = MPI_Wtime();
    printf("The program took %f seconds to run.\n", time_end - time_start);
}

free(local_primes);

MPI_Finalize();

return 0;
}

