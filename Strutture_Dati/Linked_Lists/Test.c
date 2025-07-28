#include <stdio.h>
#include <stdlib.h>

// Definizione nodo
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Funzione per aggiungere un nodo in coda
void append(Node** head, int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Funzione per rimuovere il primo nodo con un valore specifico
void removeValue(Node** head, int value) {
    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data == value) {
            if (prev == NULL) { // rimuove testa
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;  // rimuove solo la prima occorrenza
        }
        prev = current;
        current = current->next;
    }
}

// Funzione per stampare tutta la lista
void printList(Node* head) {
    for (Node* current = head; current != NULL; current = current->next) {
        printf("%d -> ", current->data);
    }
    printf("NULL\n");
}

// Uso sensato: mantiene una lista di numeri e consente inserimento e rimozione
int main() {
    Node* list = NULL;

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    printf("Initial list: ");
    printList(list);

    removeValue(&list, 20);
    printf("After removing 20: ");
    printList(list);

    append(&list, 40);
    printf("After adding 40: ");
    printList(list);

    // Pulizia finale: libera la memoria
    while (list != NULL) {
        Node* tmp = list;
        list = list->next;
        free(tmp);
    }

    return 0;
}
