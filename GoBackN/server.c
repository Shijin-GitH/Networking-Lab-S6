// Server.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int port, server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[100];

    printf("Enter port number: ");
    scanf("%d", &port);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    client_len = sizeof(client_addr);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    printf("Connection established...\n");

    static int seq_num = 0;
    static int expected_seq_num = 0;

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Received message: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        // Check if the received packet is the expected one
        if (expected_seq_num == seq_num)
        {
            // Send acknowledgment with sequence number
            sprintf(buffer, "Acknowledged Packet %d", expected_seq_num);
            send(client_fd, buffer, strlen(buffer) + 1, 0);
            expected_seq_num++;
        }
        else
        {
            // Ignore out-of-order packets
            printf("Out-of-order packet received, ignoring...\n");
        }
    }
    close(client_fd);
}
