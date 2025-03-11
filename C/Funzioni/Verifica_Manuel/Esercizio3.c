#include <stdio.h>

int A, B, verifica, sommatoria = 0, fattoriale = 1; 

void calcolo (int *a, int *b) {
    //Sommatoria
    for (int i = 1; i <= *a; i++) {
        sommatoria += i;
    }
    //Fattoriale
    for (int i = 1; i <= *b; i++) {
        fattoriale = fattoriale * i;
    }
    if (sommatoria > fattoriale) {
        *a = 1;
        *b = 0;
    } else {
        *a = 0;
        *b = 1;
    }
}

int main () {
    printf ("Inserire i numeri di cui si vuole confrontare la sommatoria e la fattoriale: ");
    scanf ("%d", &A);
    scanf ("%d", &B);
    calcolo (&A, &B);
    if (A == 1 && B == 0) {
        printf ("La sommatoria e' maggiore della fattoriale");
    }
    else {
        printf ("La sommatoria e' minore della fattoriale");
    }
}