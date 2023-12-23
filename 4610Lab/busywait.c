// Busy-waiting program : CSE 5250 programming assignment #2 by Mario Valdez
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The global variables are here
long long int n = 1000000;
long long int thread_count;
double sum = 0;

// The flag; set this to zero
int flag = 0;

// Prototype
void* Thread_sum(void* rank) {
    long long int my_rank = (long long int)rank;
    double factor;
    long long int i;
    long long int my_n = n / thread_count;
    long long int my_first_i = my_n * my_rank;
    long long int my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    // Important for loop
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {

        // actual busy waiting
        while (flag != my_rank)
            ;

        sum += factor / (2 * i + 1);

        // Increment the flag please
        flag = (flag + 1) % thread_count;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    thread_count = strtol(argv[1], NULL, 10);

    pthread_t* thread_handles;
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

    for (long long int thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread);
    }

    for (long long int thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    printf("Estimated value of pi: %.15f\n", 4.0 * sum);
    return 0;
}
