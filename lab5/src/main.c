#include <stdio.h>
#include <deamon.h>


void help(const char* prog_name){
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\t%s TRACKFILE\n", prog_name);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        help(argv[0]);
        return 1;
    }

    int pid=run_deamon(argv[1]);
    if (!pid)
        return 0;

    printf("%d\n", pid);
    return 0;
}
