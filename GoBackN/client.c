// Client.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
    int port, client_fd;
    struct sockaddr_in server_addr;
    char buffer[100], ack[100];
    char messages[100][100];
    int seq_num = 0, window_size, base = 0, next_seq_num = 0;
    int i, total_packets, packets_sent = 0;

    printf("Enter port number: ");
    scanf("%d", &port);
    printf("Enter total number of packets: ");
    scanf("%d", &total_packets);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    for (i = 0; i < total_packets; i++)
    {
        printf("Enter message for Packet %d: ", i);
        scanf("%s", messages[i]);
    }

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server...\n");

    while (base < total_packets)
    {
        // Send packets in the current window
        for (i = 0; i < window_size && next_seq_num < total_packets; i++)
        {
            send(client_fd, messages[next_seq_num], strlen(messages[next_seq_num]) + 1, 0);
            printf("Sent: %s\n", messages[next_seq_num]);
            next_seq_num++;
        }

        // Wait for acknowledgment
        memset(ack, 0, sizeof(ack));
        if (recv(client_fd, ack, sizeof(ack), 0) > 0)
        {
            int ack_num;
            sscanf(ack, "Acknowledged Packet %d", &ack_num);
            printf("Received: %s\n", ack);

            if (ack_num >= base)
            {
                base = ack_num + 1; // Slide the window
            }
        }
        else
        {
            // Timeout or error, resend all packets in the window
            printf("Timeout or error, resending window...\n");
            next_seq_num = base; // Reset next_seq_num to base
            for (i = base; i < base + window_size && i < total_packets; i++)
            {
                send(client_fd, messages[i], strlen(messages[i]) + 1, 0);
                printf("Resent: %s\n", messages[i]);
            }
        }
    }

    // Send exit message to close the connection
    strcpy(buffer, "exit");
    send(client_fd, buffer, strlen(buffer) + 1, 0);

    close(client_fd);
}
