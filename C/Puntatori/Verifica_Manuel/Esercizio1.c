#include <stdio.h>

int main () {
    int a, b;
    do {
        printf ("Inserisci i valori per il lato del rettangolo (b e h): ");
        scanf ("%d %d", &a, &b);
    } while (a <= 0 || b <= 0);

    for (int i=0; i<b; i++) {
        for (int j=0; j<a; j++) {
            if ((i+j) % 2 == 0) {
                printf ("# ");
            }
            else {
                printf ("* ");
            }
        }

        printf ("\n");
    }

}