#include <stdio.h>

int main(void) {
    int a[5] = {1, 2, 3, 4, 5};
    unsigned int total = 0;
    // out of bounds,j should less than sizeof(a)/sizeof(int)
    for (int j = 0; j < sizeof(a); j++) {
        total += a[j];
    }
    printf("sum of array is %d\n", total);

    return 0;
}
