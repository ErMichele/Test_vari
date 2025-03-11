#include <stdio.h>
int a, b, somma;
int *pa = &a, *pb = &b;
int main () {
    do {
        printf ("Scrivere i due numeri di cui fare la somma ripetuta (prodotto): ");
        scanf ("%d %d", pa, pb);
    } while (*pa <= *pb);
    
    for (int i = 0; i < *pa; i++) {
        somma += *pb;
    }
    printf ("%d", somma);
}
