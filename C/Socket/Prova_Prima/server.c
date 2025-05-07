#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    SOCKET socket;
    char username[50];
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;
CRITICAL_SECTION lock;

void broadcast_message(const char *message, SOCKET sender_socket) {
    EnterCriticalSection(&lock);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender_socket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    LeaveCriticalSection(&lock);
}

DWORD WINAPI handle_client(LPVOID arg) {
    SOCKET client_socket = *(SOCKET *)arg;
    char buffer[BUFFER_SIZE], username[50];

    recv(client_socket, username, sizeof(username), 0);
    strcpy(clients[client_count].username, username);
    clients[client_count].socket = client_socket;
    client_count++;

    printf("%s si è connesso!\n", username);

    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;

        char message[BUFFER_SIZE];
        sprintf(message, "%s: %s", username, buffer);
        printf("%s\n", message);
        
        broadcast_message(message, client_socket);
    }

    closesocket(client_socket);
    return 0;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, MAX_CLIENTS);

    printf("Server in ascolto sulla porta %d...\n", PORT);

    InitializeCriticalSection(&lock);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        CreateThread(NULL, 0, handle_client, &client_socket, 0, NULL);
    }

    DeleteCriticalSection(&lock);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
