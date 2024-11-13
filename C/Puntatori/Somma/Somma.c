//Scrivi una funzione che prenda due numeri interi e restituisca la loro somma utilizzando i puntatori.
#include <stdio.h>
#include <windows.h>

int main() {
    int a = 5, b = 10, risultato;
    int *ptrA = &a; // Puntatore a 'a'
    int *ptrB = &b; // Puntatore a 'b'
    int *ptrRisultato = &risultato; // Puntatore a 'risultato'

    *ptrRisultato = *ptrA + *ptrB; // Somma tramite puntatori
    printf("La somma e': %d\n", risultato);
    Sleep (10000);
    return 0;
}
