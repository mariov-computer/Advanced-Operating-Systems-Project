#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
    //take in a thread count
    int thread_count = strtol(argv[1], NULL, 10);

    //create an array
    const int n = 40;
    int fibo[n];
    fibo[0] = fibo[1] = 1;



//calculate the first n fibonacci numbers
    for(int i = 2; i < n; i++){
       fibo[i] = fibo[i - 1] + fibo[i-2];
    }

    //print fibo numbers
    printf("The fibonacci numbers are:\n");
    for(int i = 0; i < n; i++){
        printf("%d ", fibo[i]);
    }

    printf("End of numbers reached\n");

    return 0;
}