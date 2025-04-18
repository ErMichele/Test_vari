/*
Creare una funzione ricorsiva in C che prenda in input un numero intern n.
La funzione deve calcolare la serie armonica del numero n.
Dicasi serie armonica la sommatoria che da 1/1 a 1/n.
Quindi la sommatoria di 1/x, dove x `e un valore compreso tra 1 ed n.
*/

#include <stdio.h>

int serieArmonica (int x) {
    if (x == 1) {
        return 1;
    } else {
        return 1.0 / x + serieArmonica(x - 1);
    }
}

int main() {
    int x;

    printf("Inserisci il numero: ");
    scanf("%d", &x);

    float Serie = serieArmonica(x);
    printf("%.2f", Serie);
}