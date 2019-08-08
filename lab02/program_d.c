int main(void) {
    int a[20];
    for (int i = 0;; i++) {
        a[i] = i;
    }
    // segmentation fault
    return 0;
}
