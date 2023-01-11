#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main() {
    double X[9999], Y[9999];
    int i, count = 0;

    srand(time(0)); // Initialize random seed

    #pragma omp parallel for schedule(static) private(i)
    for (i = 0; i < 9999; i++) {
        double rng1 = (double)rand()/RAND_MAX;
        double rng2 = (double)rand()/RAND_MAX;
        X[i] = rng1;
        Y[i] = rng2;
    }

    #pragma omp parallel for schedule(static) private(i) reduction(+:count)
    for (i = 0; i < 9999; i++) {
        if ((X[i] * X[i] + Y[i] * Y[i]) < 1) {
            count++;
        }
        int p = omp_get_num_threads();
        printf("%d\n",p);
    }

    double pi = 4.0 * count / 9999;
    printf("%f", pi);
    return 0;
}