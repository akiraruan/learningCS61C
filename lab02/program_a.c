#include <stdio.h>
#include <stdlib.h>

int *pi;

void f(void) {
    pi = malloc(sizeof(int));
    *pi = 3;
    printf("*pi is %d\n", *pi);
    free(pi);
}

int main(void) {
    pi = malloc(sizeof(int));
    *pi = 4;
    f();

    return 0;
}
