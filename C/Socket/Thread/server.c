#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

void *handle_client(void *client_socket) {
    int sock = *(int*)client_socket;
    char buffer[BUFFER_SIZE] = {0};

    // Ricezione del messaggio dal client
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Messaggio ricevuto: %s\n", buffer);

    // Risposta al client
    send(sock, "Messaggio ricevuto!", strlen("Messaggio ricevuto!"), 0);

    // Chiusura del socket
    #ifdef _WIN32
        closesocket(sock);
    #else
        close(sock);
    #endif

    free(client_socket);
    return NULL;
}

int main() {
    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            printf("Errore WSAStartup: %d\n", WSAGetLastError());
            return 1;
        }
    #endif

    int server_fd, *new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Creazione del socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Errore nella creazione del socket");
        return 1;
    }

    // Configurazione dell'indirizzo
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Associazione del socket alla porta
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Errore nel binding");
        return 1;
    }

    // Messa in ascolto
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Errore nella listen");
        return 1;
    }
    printf("Server in ascolto sulla porta %d...\n", PORT);

    while (1) {
        // Accettazione della connessione
        new_socket = malloc(sizeof(int));
        *new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (*new_socket < 0) {
            perror("Errore nell'accept");
            free(new_socket);
            continue;
        }
        printf("Nuovo client connesso!\n");

        // Creazione di un thread per gestire il client
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void*)new_socket);
        pthread_detach(thread_id); // Rilascia il thread dopo la sua esecuzione
    }

    #ifdef _WIN32
        closesocket(server_fd);
        WSACleanup();
    #else
        close(server_fd);
    #endif

    return 0;
}
