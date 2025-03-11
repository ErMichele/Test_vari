#include <stdio.h>

int n, valore, risultato, prodotto = 1;

int operazione (int n) {
    for (int i = 0; i < n; i++) {
        printf ("%d/%d  Inserisci il numero: ", i+1, n);
        scanf ("%d", &valore);
        prodotto = prodotto * valore;
    }
    return prodotto;
}

int main () {
    printf ("Scrivere il numero di valori che si vuole inseriere: ");
    scanf ("%d", &n);
    risultato = operazione (n);
    printf ("Il prodotto di tutti i numeri e' uguale a %d", risultato);
}