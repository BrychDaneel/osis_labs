#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void help(){
}


int main(int argc, char* argv[]){

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <=0 ){
        fprintf(stderr, "FAILED to create socket");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((unsigned short) 27015);

    if (connect(sock, (struct sockaddr*) &address, sizeof(struct sockaddr_in)) < 0){
        fprintf(stderr, "FAILED to connect");
        return 2;
    }

    while (!feof(stdin)){
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);
        send(sock, buf, sizeof(buf), 0);
        int recv_size = recv(sock, buf, sizeof(buf), 0);
        buf[recv_size] = '\0';
        printf("RECV: %s", buf);
    }

    close(sock);

    return 0;
}
