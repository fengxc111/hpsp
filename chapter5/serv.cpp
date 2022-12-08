#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop = false;
static void handle_term(int sig )
{
    stop = true;
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, handle_term);

    if (argc <= 2){
        // printf("usage: %s ip_address prot_number backlog\n", basename(argv[0]));
        printf("usage: %s ip_address prot_number\n", argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    int connfd = accept(sock, (struct sockaddr*)NULL, NULL);
    if (connfd < 0){
        printf("errno is: %d\n", errno);
    }else{
        struct sockaddr_in connaddr, peeraddr;
        socklen_t connlen = sizeof(connaddr), peerlen = sizeof(peeraddr);
        // getsockname local
        getsockname(connfd, (struct sockaddr *)&connaddr, &connlen);
        printf("local addr = %s:%d\n", inet_ntoa(connaddr.sin_addr), ntohs(connaddr.sin_port));

        // get peername remote
        getsockname(connfd, (struct sockaddr*)&peeraddr, &peerlen);
        printf("remote addr = %s:%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
    }

    while (!stop){
        sleep(1);
    }

    close(sock);
    return 0;
}