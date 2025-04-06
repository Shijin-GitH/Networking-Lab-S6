// Stop N Wait - Client.c

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int client_fd, port;
    struct sockaddr_in server_addr;
    char buffer[100], ack[20];

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
        send(client_fd, buffer, strlen(buffer) + 1, 0);
        if (strcmp(buffer, "exit") == 0)
            break;
        sleep(2); // Simulate network delay

        // Simulate a case where acknowledgment is not received
        if (strcmp(buffer, "noack") == 0)
        {
            printf("No acknowledgment received, resending packet.....\n");
            sleep(1);
            printf("Sending: %s\n", buffer);
            sleep(3); // Delay for 3 seconds
            send(client_fd, "noack", sizeof("noack"), 0);
        }
        recv(client_fd, ack, sizeof(ack), 0);
        printf("ACK: %s\n", ack);
    }

    close(client_fd);
}