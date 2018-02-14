#include <stdio.h>
#include <procinfo.h>
#include <string.h>


void help(){
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\tlab4 -l\n");
    fprintf(stderr, "\tlab4 -p PID\n");
}

int main(int argc, char* argv[]){
    if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))){
        help();
        return 0;
    }
    if (argc == 2 && !strcmp(argv[1], "-l")){
        printProcList();
        return 0;
    }
    if (argc == 3 && !strcmp(argv[1], "-p")){
        int pid;
        char temp;
        if (sscanf(argv[2], "%d%1[^\n]", &pid, &temp) == 1){
            printProcInfo(pid);
            return 0;
        }
    }
    help();
    return 1;
}
