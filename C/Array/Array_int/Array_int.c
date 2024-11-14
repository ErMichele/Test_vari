#include <stdio.h>

int main() {
    printf ("|Calcolatore di medie|   Inserisci il numero dei valori che vuoi calcolare, e poi i vari valori per fare la media tra questi:");
    int numeri;
    float input;
    float media=0;
    scanf("%d", &numeri);
    int Lista_numeri[numeri];
    for (int i=0;i<numeri;i++) {
        scanf ("%f", &input);
        Lista_numeri[i]=input;
    }
    for (int i = 0; i < numeri; i++) {
        if (i< numeri - 1){
            printf("%d, ", Lista_numeri[i] );
        }
        else {
            printf("%d.", Lista_numeri[i] );
        }
    }
    return 0;
}