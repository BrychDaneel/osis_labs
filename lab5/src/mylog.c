#include <stdio.h>
#include <time.h>


void log_mesg(const char* message){
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);
    FILE* flog = fopen("/home/daneel/prog/osis/lab5/deamon.log", "a");
    fprintf(flog, "%04d/%02d/%02d %02d:%02d:%02d    %s\n", aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec, message);
    fclose(flog);
}
