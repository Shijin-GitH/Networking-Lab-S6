#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int reverse(int n) {
    int rev = 0;
    while (n != 0) {
        rev = rev * 10 + n % 10;
        n = n / 10;
    }
    return rev;
}

int main() {
    int server_fd, port, num, rev_num;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);

    printf("Enter port number: ");
    scanf("%d", &port);

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("Server Listening on port %d...\n", port);

    sendto(server_fd, "Enter an integer: ", strlen("Enter an integer: "), 0, (struct sockaddr*)&clientaddr, len);
    recvfrom(server_fd, &num, sizeof(num), 0, (struct sockaddr*)&clientaddr, &len);
    printf("Number received: %d\n", num);

    rev_num = reverse(num);
    printf("Number sent: %d\n", rev_num);
    
    sendto(server_fd, &rev_num, sizeof(rev_num), 0, (struct sockaddr*)&clientaddr, len);

    close(server_fd);
    return 0;
}
