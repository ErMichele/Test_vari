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
#define MAX_CLIENTS 10

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int sender_sock) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] != sender_sock) {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&lock);
}

void *handle_client(void *client_socket) {
    int sock = *(int*)client_socket;
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }

        printf("Messaggio ricevuto: %s\n", buffer);
        broadcast_message(buffer, sock);
    }

    pthread_mutex_lock(&lock);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == sock) {
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

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

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Errore nella creazione del socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Errore nel binding");
        return 1;
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Errore nella listen");
        return 1;
    }
    printf("Server in ascolto sulla porta %d...\n", PORT);

    while (1) {
        new_socket = malloc(sizeof(int));
        *new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (*new_socket < 0) {
            perror("Errore nell'accept");
            free(new_socket);
            continue;
        }

        pthread_mutex_lock(&lock);
        clients[client_count++] = *new_socket;
        pthread_mutex_unlock(&lock);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void*)new_socket);
        pthread_detach(thread_id);
    }

    #ifdef _WIN32
        closesocket(server_fd);
        WSACleanup();
    #else
        close(server_fd);
    #endif

    return 0;
}
