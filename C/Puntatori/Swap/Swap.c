#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 10, b = 20;
    printf("Prima dello swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);  // Passaggio dei puntatori a swap
    printf("Dopo lo swap: a = %d, b = %d\n", a, b);
    return 0;
}
