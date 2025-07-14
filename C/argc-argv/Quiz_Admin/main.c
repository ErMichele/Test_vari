#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAMPO 1000

void admin_menu();
void gioca_quiz();
void aggiungi_domanda();

int main(int argc, char *argv[]) {
    if (argc == 4 && strcmp(argv[1], "-a") == 0) {
        // Autenticazione admin
        char *input_id = argv[2];
        char *input_password = argv[3];

        FILE *file = fopen("admin.txt", "r");
        if (file == NULL) {
            perror("Errore nell'apertura del file admin.txt");
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
            admin_menu();
        } else {
            printf("Accesso negato. ID o password errati.\n");
            return 1;
        }
    } else if (argc == 1) {
        printf("Modalità GIOCATORE: Benvenuto al quiz!\n");
        gioca_quiz();
    } else {
        printf("Uso corretto:\n");
        printf("  %s -a <id> <password>   // modalità admin\n", argv[0]);
        printf("  %s                      // modalità giocatore\n", argv[0]);
        return 2;
    }

    return 0;
}

void admin_menu() {
    int scelta;
    do {
        printf("\n--- Menu Admin ---\n");
        printf("1. Aggiungi nuova domanda\n");
        printf("2. Esci\n");
        printf("Scelta: ");
        if (scanf("%d", &scelta) != 1) {
            while (getchar() != '\n'); // pulisce input non valido
            scelta = 0;
        }
        getchar(); // consuma \n

        if (scelta == 1) {
            aggiungi_domanda();
        } else if (scelta != 2) {
            printf("Scelta non valida, riprova.\n");
        }
    } while (scelta != 2);
}

void aggiungi_domanda() {
    char domanda[MAX_CAMPO], r1[MAX_CAMPO], r2[MAX_CAMPO], r3[MAX_CAMPO];
    int corretta;

    printf("Inserisci la domanda: ");
    fgets(domanda, MAX_CAMPO, stdin);
    strtok(domanda, "\n");

    printf("Risposta A: ");
    fgets(r1, MAX_CAMPO, stdin);
    strtok(r1, "\n");

    printf("Risposta B: ");
    fgets(r2, MAX_CAMPO, stdin);
    strtok(r2, "\n");

    printf("Risposta C: ");
    fgets(r3, MAX_CAMPO, stdin);
    strtok(r3, "\n");

    do {
        printf("Qual è la risposta corretta? (1=A, 2=B, 3=C): ");
        if (scanf("%d", &corretta) != 1) {
            while (getchar() != '\n'); // pulisce input non valido
            corretta = 0;
        }
        getchar(); // consuma \n

        if (corretta < 1 || corretta > 3)
            printf("⚠️  Inserisci un numero tra 1 e 3.\n");
    } while (corretta < 1 || corretta > 3);

    FILE *quiz = fopen("quiz.txt", "a");
    if (quiz == NULL) {
        perror("Errore apertura quiz.txt");
        return;
    }

    fprintf(quiz, "%s|%s|%s|%s|%d\n", domanda, r1, r2, r3, corretta);
    fclose(quiz);

    printf("Domanda aggiunta con successo!\n");
}

void gioca_quiz() {
    FILE *quiz = fopen("quiz.txt", "r");
    if (quiz == NULL) {
        perror("Errore apertura quiz.txt");
        return;
    }

    char linea[MAX_CAMPO];
    char domanda[MAX_CAMPO], r1[MAX_CAMPO], r2[MAX_CAMPO], r3[MAX_CAMPO];
    int corretta, risposta, punteggio = 0, totale = 0;

    while (fgets(linea, sizeof(linea), quiz)) {
        // Parse la linea secondo il formato domanda|r1|r2|r3|corretta
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%d", domanda, r1, r2, r3, &corretta) != 5) continue;

        printf("\nDomanda: %s\n", domanda);
        printf("1. %s\n2. %s\n3. %s\nRisposta: ", r1, r2, r3);

        if (scanf("%d", &risposta) != 1) {
            while (getchar() != '\n'); // pulisce input errato
            printf("⚠️  Risposta non valida! Saltata.\n");
            totale++;
            continue;
        }
        getchar(); // consuma \n

        if (risposta < 1 || risposta > 3) {
            printf("⚠️  Risposta non valida! Saltata.\n");
        } else if (risposta == corretta) {
            printf("✅ Corretta!\n");
            punteggio++;
        } else {
            printf("❌ Sbagliato. Risposta corretta: %d\n", corretta);
        }
        totale++;
    }

    fclose(quiz);

    if (totale == 0) {
        printf("⚠️  Nessuna domanda trovata nel quiz.\n");
        return;
    }

    printf("\nHai totalizzato %d punti su %d domande.\n", punteggio, totale);
}
