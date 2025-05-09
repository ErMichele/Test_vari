#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t; // Define socklen_t for Windows
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

    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Errore nella creazione del socket");
        return 1;
    }

    // 2. Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3. Bind socket to port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Errore nel binding");
        return 1;
    }

    // 4. Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Errore nella listen");
        return 1;
    }
    printf("Server in ascolto sulla porta %d...\n", PORT);

    // 5. Accept client connection
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        perror("Errore nell'accept");
        return 1;
    }
    printf("Connessione accettata!\n");

    // 6. Receive and respond
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Messaggio ricevuto: %s\n", buffer);
    send(new_socket, "Messaggio ricevuto!", strlen("Messaggio ricevuto!"), 0);

    // 7. Close sockets
    #ifdef _WIN32
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
    #else
        close(new_socket);
        close(server_fd);
    #endif

    return 0;
}
