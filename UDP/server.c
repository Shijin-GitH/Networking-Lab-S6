#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int server_fd, port;
    struct sockaddr_in server_addr, client_addr;
    char buffer[100], response[200];
    socklen_t client_len = sizeof(client_addr);

    printf("Enter port number: ");
    scanf("%d", &port);

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        recvfrom(server_fd, response, sizeof(response), 0, (struct sockaddr *)&client_addr, &client_len);
        if (strcmp(response, "exit") == 0)
            break;
        printf("Received: %s\n", response);
        printf("Enter message: ");
        scanf("%s", buffer);
        sendto(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, client_len);
    }

    close(server_fd);
}