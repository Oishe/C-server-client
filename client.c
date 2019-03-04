#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main()
{
    int status;
    struct sockaddr_in their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd;
    struct timeval tvalBefore, tvalAfter;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET;       // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;  // UDP stream sockets

    status = getaddrinfo("127.0.0.1", "5555", &hints, &res);
    // res now points to a linked list of 1 or more struct addrinfos

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    memset(&their_addr, '\0', sizeof(their_addr));
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(5555);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_size = sizeof(their_addr);

    int bytes_transfered;
    char msg[BUFSIZE];
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    int len = BUFSIZE;

    int x;
    for (x = 0; x < 1000; x++)
    {
        msg[x] = 'x';
    }
    msg[x + 1] = '\n';

    // strcpy(msg, "hello from C\n");
    printf("Sent: %s\n", msg);
    gettimeofday(&tvalBefore, NULL);
    bytes_transfered = sendto(sockfd, msg, len, 0, (struct sockaddr *)&their_addr, addr_size);

    bytes_transfered = recvfrom(sockfd, buf, len, 0, (struct sockaddr *)&their_addr, &addr_size);
    gettimeofday(&tvalAfter, NULL);
    float microsecs = (tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L + tvalAfter.tv_usec - tvalBefore.tv_usec;
    printf("Recieved: %s\n", buf);
    printf("Time in microseconds: %f us\n", microsecs); // Added semicolon
    float bit_per_sec = bytes_transfered * 8 / microsecs * 1000;
    printf("Bits per second: %f bits/s\n", bit_per_sec); // Added semicolon
    shutdown(sockfd, 2);
    freeaddrinfo(res); // free the linked-list
    printf("Complete\n");
}