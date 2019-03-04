#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
    int status;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd;
    // int new_fd;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET;       // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;  // UDP stream sockets

    status = getaddrinfo("127.0.0.1", "5555", &hints, &res);
    // res now points to a linked list of 1 or more struct addrinfos

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    // listen(sockfd, 20);

    // addr_size = sizeof their_addr;
    // new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    int bytes_transfered;
    unsigned int microsecs = 10000;
    char buf[BUFSIZE];
    while (1)
    {
        memset(buf, 0, BUFSIZE);
        int len = BUFSIZE;
        bytes_transfered = recvfrom(sockfd, buf, len, 0, (struct sockaddr *)&their_addr, &addr_size);
        // usleep(microsecs);
        bytes_transfered = sendto(sockfd, buf, len, 0, (struct sockaddr *)&their_addr, addr_size);
        printf("Recieved: %s", buf);
        // printf("Sleep for: %d us\n", microsecs);
    }

    shutdown(sockfd, 2);
    freeaddrinfo(res); // free the linked-list
    printf("Complete\n");
}