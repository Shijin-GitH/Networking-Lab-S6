#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_fd, port, num, result;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    char message[50];

    printf("Enter the port number: ");
    scanf("%d", &port);

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    printf("Trying to communicate with Server....\n");

    sendto(client_fd, "Hello, Server", strlen("Hello, Server"), 0, (struct sockaddr *)&serveraddr, len);

    recvfrom(client_fd, message, sizeof(message), 0, (struct sockaddr *)&serveraddr, &len);
    printf("\n%s", message);

    scanf("%d", &num);
    sendto(client_fd, &num, sizeof(num), 0, (struct sockaddr *)&serveraddr, len);

    recvfrom(client_fd, &result, sizeof(result), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Result is %d\n", result);

    close(client_fd);
    return 0;
}
