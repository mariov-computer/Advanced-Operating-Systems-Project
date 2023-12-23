#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
    //take in a thread count
    int thread_count = strtol(argv[1], NULL, 10);

    //Calculate the number pi using a summation
    double factor = 1.0;
    double sum = 0.0;
    int n = 1000;

#pragma omp parallel for num_threads(thread_count) \
 reduction(+: sum) private(factor)
    for(int k = 0; k < n; k ++){
        if (k % 2 == 0) factor = 1.0;
        else factor = -1.0;



        sum += factor / (2.0 * k + 1);
    }

    //Our approximated value of pi is 4 times the sum
    double pi_approx = 4.0 * sum;

    //Print pi to around 18 decimal places
    printf("Pi approximated using %d terms is:\n", n);
    printf("%.18f\n", pi_approx);

    return 0;
}