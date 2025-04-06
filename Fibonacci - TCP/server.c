#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

void fibonacci(int n, int arr[])
{
    int a = 0, b = 1, c = 2;
    for (int i = 0; i < n; i++)
    {
        arr[i] = a;
        a = b;
        b = c;
        c = a + b;
    }
}

int main()
{
    int server_fd, client_fd, port, num;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    printf("Server listening on port %d...\n", port);
    bind(server_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    len = sizeof(clientaddr);

    listen(server_fd, 5);
    client_fd = accept(server_fd, (struct sockaddr *)&clientaddr, &len);
    printf("Connection established!\n");

    send(client_fd, "Enter how many numbers: ", sizeof("Enter how many numbers: "), 0);
    recv(client_fd, &num, sizeof(num), 0);

    int arr[num];
    fibonacci(num, arr);

    send(client_fd, arr, sizeof(arr), 0);

    close(server_fd);
}
