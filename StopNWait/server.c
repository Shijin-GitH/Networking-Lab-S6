// Stop N Wait - Server.c

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int server_fd, client_fd, port;
    struct sockaddr_in server_addr;
    char buffer[100], response[200];

    printf("Enter port number: ");
    scanf("%d", &port);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    client_fd = accept(server_fd, NULL, NULL);

    while (1)
    {
        recv(client_fd, buffer, sizeof(buffer) + 1, 0);
        if (strcmp(buffer, "exit") == 0)
            break;

        // Simulate a case where acknowledgment is not sent
        if (strcmp(buffer, "noack") == 0)
            recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Received: %s\n", buffer);
        sprintf(response, "Received \'%s\'", buffer);
        send(client_fd, response, strlen(response) + 1, 0);
    }

    close(server_fd);
    close(client_fd);
}