#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_fd, port, num, arr[100];
    struct sockaddr_in serveraddr;
    char message[100];
    socklen_t len;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    printf("Trying to connect with Server....\n");
    connect(client_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Connected with server...\n");

    recv(client_fd, &message, sizeof(message), 0);
    printf("%s", message);
    scanf("%d", &num);

    send(client_fd, &num, sizeof(num), 0);
    recv(client_fd, &arr, sizeof(arr), 0);

    printf("Fibonacci Sequence: ");
    for (int i = 0; i < num; i++)
        printf("%d ", arr[i]);

    close(client_fd);
}