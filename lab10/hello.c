#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel
    {
        int thread_ID = omp_get_thread_num();
        printf("Hello world: %d\n", thread_ID);
    }
}
