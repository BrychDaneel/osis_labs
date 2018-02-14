#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int udp_server(int port){

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return 1;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(27015);

    if (bind(sock, (struct sockaddr*) &address, sizeof(address)) < 0)
        return 2;

    while (1){
        char buf[1024];
        socklen_t adr_len = sizeof(address);
        int recv_size = recvfrom(sock, buf, sizeof(buf), 0,
                                 (struct sockaddr *)&address, &adr_len);
        buf[recv_size] = '\0';
        sendto(sock, buf, recv_size, 0,
               (struct sockaddr *)&address, sizeof(address));
    }
    return 0;
}
