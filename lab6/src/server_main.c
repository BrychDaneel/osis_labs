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
#include <tcp_server.h>
#include <udp_server.h>


void help(const char* prog){
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "\t%s [-u|-t] PORT\n", prog);
}


int run_tcp_server(int port){
    int pid = fork();
    if (pid == -1){
        fprintf(stderr, "Can't fork.\n");
        return 1;
    }

    if (!pid){
        umask(0);
        setsid();
        chdir("/");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        return tcp_server(port);
    }

    printf("%d\n", pid);
    return 0;
}


int run_udp_server(int port){
    int pid = fork();
    if (pid == -1){
        fprintf(stderr, "Can't fork.\n");
        return 1;
    }

    if (!pid){
        umask(0);
        setsid();
        chdir("/");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        return udp_server(port);
    }

    printf("%d\n", pid);
    return 0;
}

int main(int argc, char* argv[]){
    char c;
    int port;
    if (argc==2 && sscanf(argv[1], "%d%1s", &port, &c)==1)
        return run_tcp_server(port);

    if (argc==3 && !strcmp(argv[1], "-t") && sscanf(argv[2], "%d%1s", &port, &c)==1)
        return run_tcp_server(port);

    if (argc==3 && !strcmp(argv[1], "-u") && sscanf(argv[2], "%d%1s", &port, &c)==1)
        return run_udp_server(port);

    help(argv[0]);
    return 1;
}
