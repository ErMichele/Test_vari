/*
Creare una funzione ricorsiva in C che prenda in input una variabile n (di tipo int).
La funzione, in modo ricorsivo deve calcolare la somma delle sue cifre intere e restituire quindi il
risultato.
ESEMPIO: Se n = 1234, la funzione deve restituire 10, in quanto 1 + 2 + 3 + 4 = 10.
*/

#include <stdio.h>

int SommaCifre (int x) {
    if (x == 0) {
        return 0;
    } else {
        return x % 10 + SommaCifre(x / 10);
    }
}

int main() {
    int x;

    printf("Inserisci il numero: ");
    scanf("%d", &x);

    int Somma = SommaCifre(x);
    printf("%d", Somma);
}