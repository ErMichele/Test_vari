#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Settembre";
    char str2[100];

    printf("Inserisci una stringa: ");
    scanf("%99s", str2);  // Legge una stringa dall'utente

    if (strcmp(str1, str2) == 0) {
        printf("Le stringhe sono uguali.\n");
    } else {
        printf("Le stringhe sono diverse.\n");
    }

    return 0;
}