#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            printf("Errore WSAStartup: %d\n", WSAGetLastError());
            return 1;
        }
    #endif

    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};

    // Creazione del socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Errore nella creazione del socket");
        return 1;
    }

    // Configurazione dell'indirizzo del server
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("172.16.1.55");

    // Connessione al server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Errore nella connessione");
        return 1;
    }
    printf("Connesso al server!\n");

    // Invio del messaggio
    send(sock, "Ciao, server!", strlen("Ciao, server!"), 0);

    // Ricezione della risposta
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Risposta dal server: %s\n", buffer);

    // Chiusura del socket
    #ifdef _WIN32
        closesocket(sock);
        WSACleanup();
    #else
        close(sock);
    #endif

    return 0;
}
