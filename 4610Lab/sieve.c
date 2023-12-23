//Option 1: Stick with writing C code
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc, char* argv[]){
    //before the main code
    clock_t begin = clock();
    //Replace the 1000
    //And make search max an integer
    int search_max = strtol(argv[1], NULL, 10);
    int sqrt_search_max = (int)sqrt(search_max);


    //acquire the number of threads
    int thread_count = strtol(argv[2], NULL, 10);



    //pointer to a block of allocated memory
    //the amount of memory is the size of an int
    int* primes;
    primes = (int*)malloc(search_max * sizeof(int));

    for(int i =0; i< search_max; i++){
        primes[i] = i + 1;
    }
    //pragma stuff
#   pragma omp parallel num_threads(thread_count)
{

    

    for(int i = 1; i < sqrt_search_max; i++){
        int current prime = primes[i];

        if(current_prime != 0){

#   pragma omp for
            for(int j = i + current_prime; j < search_max; j+= current_prime){
                primes[j] = 0;
            }
        }
    }
}
  //  printf("The prime numbers are: ");
   // for(int i = `; i < search_max; i++){
   //     if(primes[i] != 0) printf("%d ", primes[i]);
   // }

    //Deallocate memory to avoid memory leaks
    free(primes);

    printf("End of program has been reached. \n");
    //call clock()
    clock_t end = clock();

    //print the execution time, also calculate it as well
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The program took %f seconds to run.\n", time_spent);
    return 0;
}