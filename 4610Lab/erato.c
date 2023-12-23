#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h> // Include OpenMP for parallel processing


int main(int argc, char* argv[]) {
    // Check if the command-line arguments are provided correctly
    if (argc != 3) {
        printf("Usage: %s <search_max> <thread_count>\n", argv[0]);
        return 1;
    }


    // Parse command-line arguments
    int search_max = strtol(argv[1], NULL, 10);
    int sqrt_search_max = (int)sqrt(search_max);
    int thread_count = strtol(argv[2], NULL, 10);


    // Allocate memory for the array of primes
    int* primes = (int*)malloc(search_max * sizeof(int));
    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }


    // Initialize the array with numbers from 2 to search_max
    for (int i = 0; i < search_max; i++) {
        primes[i] = i + 2; // Start from 2
    }


    clock_t begin = clock(); // Record the start time


    // Parallelize the Sieve of Eratosthenes algorithm using OpenMP
    #pragma omp parallel num_threads(thread_count)
    {
        for (int i = 2; i <= sqrt_search_max; i++) {
            if (primes[i - 2] != 0) { // -2 because we start from 2
                #pragma omp for
                for (int j = i * i; j <= search_max; j += i) {
                    primes[j - 2] = 0; // -2 because we start from 2
                }
            }
        }
    }


    // Print or save the prime numbers if needed
    // Uncomment this section if you want to print the prime numbers
    /*
    printf("The prime numbers are: ");
    for (int i = 0; i < search_max; i++) {
        if (primes[i] != 0) {
            printf("%d ", primes[i]);
        }
    }
    */


    // Deallocate memory to avoid memory leaks
    free(primes);


    clock_t end = clock(); // Record the end time


    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // Calculate execution time
    printf("The program took %f seconds to run.\n", time_spent);


    return 0;
}
