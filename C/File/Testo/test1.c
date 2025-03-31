#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

int main (){
    int m;
    FILE *file = fopen ("test1.txt", "a");
    if (file==NULL) {
        printf ("Il file non è stato trovato.\n");
        return -1;
    }
    printf ("Scrivi i numeri da mettere nel file: ");
    scanf ("%d", &m);
    fprintf (file, "%d\n", m);

    fclose (file);
}