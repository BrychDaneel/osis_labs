#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void help(){
}


int main(int argc, char* argv[]){

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock <=0 ){
        fprintf(stderr, "FAILED to create socket");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((unsigned short) 27015);

    while (!feof(stdin)){
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);
        sendto(sock, buf, sizeof(buf), 0,
               (struct sockaddr*) &address, sizeof(struct sockaddr_in));

        socklen_t adr_len = sizeof(address);
        int recv_size = recvfrom(sock, buf, sizeof(buf), 0,
                                 (struct sockaddr *)&address, &adr_len);
        buf[recv_size] = '\0';
        printf("RECV: %s", buf);
    }

    close(sock);

    return 0;
}
