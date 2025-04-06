#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

int reverse(int n) {
    int rev = 0;
    while (n != 0) {
        rev = rev * 10;
        rev = rev + n % 10;
        n = n / 10;
    }
    return rev;
}

int main() {
    int server_fd, client_fd, port, num, rev_num;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Server Listening on port %d.....", port);
    
    bind(server_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    len = sizeof(clientaddr);
    
    listen(server_fd, 5);
    client_fd = accept(server_fd, (struct sockaddr*)&clientaddr, &len);
    printf("Connection established...\n");

    send(client_fd, "Enter an integer: ", sizeof("Enter an integer: "), 0);
    recv(client_fd, &num, sizeof(num), 0);
    printf("Number received: %d\n", num);
    rev_num = reverse(num);
    printf("Number sent: %d", rev_num);
    send(client_fd, &rev_num, sizeof(rev_num),0);

    close(client_fd);
    close(server_fd);
}