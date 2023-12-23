#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long int number_of_tosses;
    long long int number_in_circle = 0;

    printf("Enter the total number of tosses: ");
    scanf("%lld", &number_of_tosses);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        long long int local_hits = 0;

        // Seed the random number generator as described in the Monte Carlo Method
        unsigned int seed = (unsigned int)(thread_id + 1);

        #pragma omp for
        for (long long int toss = 0; toss < number_of_tosses; toss++) {
            double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
            double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
            double distance_squared = x * x + y * y;

            if (distance_squared <= 1.0) {
                local_hits++;
            }
        }

        #pragma omp atomic
        number_in_circle += local_hits;
    }

    double pi_estimate = 4.0 * number_in_circle / (double)number_of_tosses;

    printf("Estimated value of π: %f\n", pi_estimate);

    return 0;
}
