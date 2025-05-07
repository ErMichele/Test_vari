#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>


#define PORT 8080
#define BUFFER_SIZE 1024

SOCKET client_socket;

DWORD WINAPI receive_messages(LPVOID arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            printf("\n%s\n> ", buffer);
            fflush(stdout);
        }
    }
    return 0;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct sockaddr_in server_addr;
    char username[50], message[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.1.123", &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Inserisci il tuo nome: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Rimuove il newline
    send(client_socket, username, strlen(username), 0);

    CreateThread(NULL, 0, receive_messages, NULL, 0, NULL);

    while (1) {
        printf("> ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;
        send(client_socket, message, strlen(message), 0);
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
