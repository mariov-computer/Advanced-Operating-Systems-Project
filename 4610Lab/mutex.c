// Second program - Mutexes : Programming Assignment #2 by Mario Valdez
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The global variables are here
long long int n = 1000; // number of terms
long long int thread_count;
double sum = 0;

// lock pointer????
pthread_mutex_t mutex;

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

    // CRITICAL SECTION IN THIS LOOP
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        // mutexes alert
        pthread_mutex_lock(&mutex);

        // critical section
        sum += factor / (2 * i + 1);

        // unlock please
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    long long int thread;
    pthread_t *thread_handles;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // get number of threads
    thread_count = strtol(argv[1], NULL, 10);

    // allocate memory here
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

    // mutex lock
    pthread_mutex_init(&mutex, NULL);

    // fork threads
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread);
    }

    // wait and join
    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // please print pi
    double pi = 4.0 * sum;
    printf("Pi approximated using %lld terms is:\n", n); // Changed %llu to %lld
    printf("%.18f\n", pi);

    // deallocate
    free(thread_handles);

    // destroy the lock
    pthread_mutex_destroy(&mutex);

    return 0;
}
