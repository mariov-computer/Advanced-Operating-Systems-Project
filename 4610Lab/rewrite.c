#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int number_of_tosses = 0;
    long long int number_in_circle = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD); // Synchronize processes before printing messages

    // Print process information using MPI_Gather
    char process_info[100];
    sprintf(process_info, "Process %d started", rank);

    char all_process_info[size * 100];
    MPI_Gather(process_info, 100, MPI_CHAR, all_process_info, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Print the gathered process information
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("%s\n", all_process_info + i * 100);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD); // Synchronize processes before input

    // Each process independently inputs the total number of tosses
    if (rank == 0) {
        printf("Enter the total number of tosses: ");
        fflush(stdout);
        scanf("%lld", &number_of_tosses);
    }

    MPI_Bcast(&number_of_tosses, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int local_tosses = number_of_tosses / size;
    long long int local_hits = 0;

    unsigned int seed = (unsigned int)(MPI_Wtime() * 1000000.0 * (rank + 1)); // Adjusted seed for uniqueness
    srand(seed);

    for (long long int toss = 0; toss < local_tosses; toss++) {
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;
        double distance_squared = x * x + y * y;
        if (distance_squared <= 1.0) {
            local_hits++;
        }
    }

    MPI_Reduce(&local_hits, &number_in_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi_estimate = 4.0 * number_in_circle / (double)number_of_tosses;
        printf("Estimated value of π: %f\n", pi_estimate);
    }

    MPI_Finalize();
    return 0;
}






