#include <stdio.h>

int main () {
    int a, b;
    int *pa = &a, *pb = &b;
    do {
        printf ("Inserisci i valori per il lato del rettangolo (b e h): ");
        scanf ("%d %d", pa, pb);
    } while (*pa <= 0 || *pb <= 0);

    for (int i=0; i<*pb; i++) {
        for (int j=0; j<*pa; j++) {
            if (i % 2 == 0) {
                printf ("B ");
            }
            else {
                printf ("R ");
            }
        }

        printf ("\n");
    }

}