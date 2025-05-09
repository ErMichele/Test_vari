#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link alla libreria Winsock

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};

    // 1. Inizializzazione di Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Errore WSAStartup: %d\n", WSAGetLastError());
        return 1;
    }

    // 2. Creazione del socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Errore nella creazione del socket: %d\n", WSAGetLastError());
        return 1;
    }

    // 3. Configurazione dell'indirizzo
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 4. Associazione del socket alla porta
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Errore nel binding: %d\n", WSAGetLastError());
        return 1;
    }

    // 5. Messa in ascolto
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Errore nella listen: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Server in ascolto sulla porta %d...\n", PORT);

    // 6. Accettazione della connessione
    int addrlen = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        printf("Errore nell'accept: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connessione accettata!\n");

    // 7. Ricezione e risposta
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Messaggio ricevuto: %s\n", buffer);
    send(new_socket, "Messaggio ricevuto!", strlen("Messaggio ricevuto!"), 0);

    // 8. Chiusura del socket
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
