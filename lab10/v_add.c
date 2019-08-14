#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10000000
#define REPEAT 100

/* Utility function to handle allocation failures. In this
 *  case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

void v_add_naive(double *x, double *y, double *z) {
#pragma omp parallel
    {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            z[i] = x[i] + y[i];
        }
    }
}

// Edit this function (Method 1)
void v_add_optimized_adjacent(double *x, double *y, double *z) {
    int num = omp_get_num_threads();
#pragma omp parallel
    {
        int curThread = omp_get_thread_num();
        for (int i = curThread; i < ARRAY_SIZE; i += num) {
            z[i] = x[i] + y[i];
        }
    }
}

// Edit this function (Method 2)
void v_add_optimized_chunks(double *x, double *y, double *z) {
    int num = omp_get_num_threads();
    int size = ARRAY_SIZE / num + 1;
#pragma omp parallel
    {
        int curThread = omp_get_thread_num();
        int start = curThread * size;
        int end = start + size;
        end = end > ARRAY_SIZE ? ARRAY_SIZE : end;
        for (int i = start; i < end; i++) {
            z[i] = x[i] + y[i];
        }
    }
}

double *gen_array(int n) {
    double *array = (double *)malloc(n * sizeof(double));
    if (array == NULL) {
        allocation_failed();
    }

    for (int i = 0; i < n; i++) {
        array[i] = drand48();
    }
    return array;
}

// Double check if it is correct
int verify(double *x, double *y,
           void (*funct)(double *x, double *y, double *z)) {
    double *z_v_add = (double *)malloc(ARRAY_SIZE * sizeof(double));
    double *z_oracle = (double *)malloc(ARRAY_SIZE * sizeof(double));
    if (z_v_add == NULL || z_oracle == NULL) {
        allocation_failed();
    }

    (*funct)(x, y, z_v_add);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        z_oracle[i] = x[i] + y[i];
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (z_oracle[i] != z_v_add[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Generate input vectors and destination vector
    double *x = gen_array(ARRAY_SIZE);
    double *y = gen_array(ARRAY_SIZE);
    double *z = (double *)malloc(ARRAY_SIZE * sizeof(double));
    if (z == NULL) {
        allocation_failed();
    }

    // Test framework that sweeps the number of threads and times each run
    double start_time, run_time;
    int num_threads = omp_get_max_threads();

    for (int i = 1; i <= num_threads; i++) {
        omp_set_num_threads(i);
        start_time = omp_get_wtime();
        for (int j = 0; j < REPEAT; j++) {
            v_add_optimized_adjacent(x, y, z);
        }
        run_time = omp_get_wtime() - start_time;
        if (!verify(x, y, v_add_optimized_adjacent)) {
            printf("v_add optimized adjacent does not match oracle\n");
            return -1;
        }
        printf("Optimized adjacent: %d thread(s) took %f seconds\n", i,
               run_time);
    }

    for (int i = 1; i <= num_threads; i++) {
        omp_set_num_threads(i);
        start_time = omp_get_wtime();
        for (int j = 0; j < REPEAT; j++) {
            v_add_optimized_chunks(x, y, z);
        }
        run_time = omp_get_wtime() - start_time;
        if (!verify(x, y, v_add_optimized_chunks)) {
            printf("v_add optimized chunks does not match oracle\n");
            return -1;
        }
        printf("Optimized chunks: %d thread(s) took %f seconds\n", i, run_time);
    }

    for (int i = 1; i <= num_threads; i++) {
        omp_set_num_threads(i);
        start_time = omp_get_wtime();
        for (int j = 0; j < REPEAT; j++) {
            v_add_naive(x, y, z);
        }
        run_time = omp_get_wtime() - start_time;
        printf("Naive: %d thread(s) took %f seconds\n", i, run_time);
    }
    return 0;
}
