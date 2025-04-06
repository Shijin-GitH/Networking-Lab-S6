#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

int main() {
    int client_fd, port, num, result;
    struct sockaddr_in serveraddr;
    char message[50];
    socklen_t len;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    len = sizeof(serveraddr);

    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);

    printf("Trying to connect with Server....\n");
    connect(client_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Connected with server...\n");

    recv(client_fd, &message, sizeof(message), 0);
    printf("\n%s", message);
    scanf("%d", &num);
    send(client_fd, &num, sizeof(num), 0);
    recv(client_fd, &result, sizeof(result), 0);

    printf("Result is %d", result);

    close(client_fd);
}