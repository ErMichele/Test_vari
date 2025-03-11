#include <stdio.h>

int n, divisore, somma = 0, verifica;

int calcolo (int n) {
    for (int i = 1; i < n; i++) {
        if (n % i == 0)
        {
            somma += i;
        }
    }
    if (somma == n) {
        return 1;
    }
    else {
        return 0;
    }
}

int main () {
    printf ("Inserire il numero che si vuole verificare la sua perfezione: ");
    scanf ("%d", &n);
    verifica=calcolo(n);
    if (verifica) {
        printf ("Il numero %d e' perfetto!", n);
    }
    else {
        printf ("Il numero %d non e' perfetto!", n);
    }
}