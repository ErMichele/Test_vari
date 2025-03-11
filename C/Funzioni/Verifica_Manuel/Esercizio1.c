#include <stdio.h>

int x, y, risultato;

int prodotto (int a, int b) {
    int somma = 0;
    for (int i = 0; i < b; i++) {
        somma += a;
    }
    return somma;
}

int main () {
    printf ("Inserire i valori di cui si vuole fare la somma ripetuta: ");
    scanf ("%d", &x);
    scanf ("%d", &y);
    risultato = prodotto (x, y);
    printf ("%d + %d = %d", x, y, risultato);
}