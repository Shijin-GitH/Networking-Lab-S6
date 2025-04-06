#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int client_fd, port;
    struct sockaddr_in server_addr;
    char buffer[100], response[100];

    printf("Enter port number: ");
    scanf("%d", &port);

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        printf("Enter message: ");
        scanf("%s", buffer);
        send(client_fd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit") == 0)
            break;
        recv(client_fd, response, sizeof(response), 0);
        printf("Received: %s\n", response);
    }

    close(client_fd);
}