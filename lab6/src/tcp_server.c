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


void *process_client(void *param){
    int sock = *(int*) param;
    free(param);
    while(1){
        char buf[1024];
        int recv_size = recv(sock, buf, sizeof(buf), 0);
        if (recv_size <= 0)
            break;
        send(sock, buf, recv_size, 0);
    }
    close(sock);
    pthread_exit(0);
}


int tcp_server(int port){

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
        return 1;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(27015);

    if (bind(listener, (struct sockaddr*) &address, sizeof(address)) < 0)
        return 2;

    listen(listener, 10);

    while (1){
        int sock = accept(listener, NULL, NULL);
        if(sock < 0)
            return 3;

        int * psock = (int*)malloc(sizeof(int));
        *psock = sock;

        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr, process_client, (void*) psock);
    }
    return 0;
}
