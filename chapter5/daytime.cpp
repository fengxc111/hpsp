#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    assert(argc == 2);
    char *host = argv[1];
    struct hostent* hostinfo = gethostbyname(host);
    assert(hostinfo);
    char str[128];
    struct servent* servinfo = getservbyname("daytime", "tcp");
    assert(servinfo);
    printf("daytime port is %d\n", ntohs(servinfo->s_port));
    char **pptr;
    pptr = hostinfo->h_addr_list;
    for (; *pptr != NULL; pptr++){
        printf("\taddress: %s\n",
               inet_ntop(hostinfo->h_addrtype, hostinfo->h_addr, str, sizeof(str)));
    }
    printf("address: %s\n", inet_ntop(hostinfo->h_addrtype, hostinfo->h_addr, str, sizeof(str)));
    //inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str));
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servinfo->s_port;
    // address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(result != -1);

    char buffer[128];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);
    buffer[result] = '\0';
    printf("the day time is: %s", buffer);
    close(sockfd);
    return 0;
}
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <stdio.h>
 
// extern int h_errno;
 
// int main(int argc, char **argv)
// {
//     if (argc != 2) {
//         printf("Use example: %s www.google.com\n", *argv);
//         return -1;
//     }
 
//     char *name = argv[1];
//     struct hostent *hptr;
 
//     hptr = gethostbyname(name);
//     if (hptr == NULL) {
//         printf("gethostbyname error for host: %s: %s\n", name, hstrerror(h_errno));
//         return -1;
//     }
//     //输出主机的规范名
//     printf("\tofficial: %s\n", hptr->h_name);
 
//     //输出主机的别名
//     char **pptr;
//     char str[INET_ADDRSTRLEN];
//     for (pptr=hptr->h_aliases; *pptr!=NULL; pptr++) {
//         printf("\ttalias: %s\n", *pptr);
//     }
 
//     //输出ip地址
//     switch (hptr->h_addrtype) {
//         case AF_INET:
//             pptr = hptr->h_addr_list;
//             for (; *pptr!=NULL; pptr++) {
//                 printf("\taddress: %s\n",
//                         inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
//             }
//             break;
//         default:
//             printf("unknown address type\n");
//             break;
//     }
 
//     return 0;
// }