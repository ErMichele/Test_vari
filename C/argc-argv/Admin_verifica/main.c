#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAMPO 50

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-a") != 0) {
        printf("Uso corretto: %s -a <id> <password>\n", argv[0]);
        return 1;
    }

    char *input_id = argv[2];
    char *input_password = argv[3];

    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file utenti.txt");
        return 1;
    }

    char id[MAX_CAMPO];
    char password[MAX_CAMPO];
    int autenticato = 0;

    while (fscanf(file, "%s %s", id, password) == 2) {
        if (strcmp(id, input_id) == 0 && strcmp(password, input_password) == 0) {
            autenticato = 1;
            break;
        }
    }

    fclose(file);

    if (autenticato) {
        printf("[ADMIN] Accesso riuscito. Benvenuto, %s.\n", input_id);
        // Azioni da amministratore qui
    } else {
        printf("Accesso negato. ID o password errati.\n");
    }

    return 0;
}
