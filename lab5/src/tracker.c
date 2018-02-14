#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <mylog.h>


#define MAX_EVENTS 1024 /*Максимальное кличество событий для обработки за один раз*/
#define LEN_NAME 100 /*Будем считать, что длина имени файла не превышает 16 символов*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*размер структуры события*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*буфер для хранения данных о событиях*/


void *track(void *param);

pthread_t start_track(const char * track_file){
    log_mesg( "Create track thread");
    pthread_t tid; /* идентификатор потока */
    pthread_attr_t attr; /* отрибуты потока */
    pthread_attr_init(&attr);

    log_mesg( "Start track thread");
    pthread_create(&tid,&attr, track, (void*) track_file);
    return tid;
}


int poison=0;
void stop_track(pthread_t track_thread){
    log_mesg("Stop track thread");
    poison = 1;
    if (!pthread_join(track_thread, NULL))
        log_mesg("Sucsessfuly stop track thread");
}


void *track(void *param){
    char* track_file = (char*) param;
    int length, i, wd;
    int fd;
    char buffer[BUF_LEN];

    log_mesg( "Init inotify");
    fd = inotify_init();
    if ( fd < 0 ) {
        log_mesg( "Couldn't initialize inotify");
        pthread_exit(0);
    }

    log_mesg("Add file to track");
    wd = inotify_add_watch(fd, track_file,
        IN_MODIFY | IN_ACCESS | IN_OPEN | IN_CLOSE_WRITE | IN_CLOSE_NOWRITE | IN_DELETE_SELF);

    if (wd == -1){
        char mesg[1000];
        sprintf(mesg, "Couldn't add watch to %s", track_file);
        log_mesg(mesg);
        pthread_exit(0);
    } else{
        char mesg[1000];
        sprintf(mesg, "Watching:: %s", track_file);
        log_mesg(mesg);
    }

    log_mesg( "Set inotify O_NONBLOCK");
    fcntl(fd, F_SETFL, O_NONBLOCK);

    log_mesg( "Start track to file");
    while(!poison)
    {
    usleep(300);
    i = 0;
    length = read( fd, buffer, BUF_LEN );
    while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];

        if (event->mask & IN_MODIFY)
            log_mesg("FILE WAS MODIFIED");
        if (event->mask & IN_ACCESS)
            log_mesg("SOMEBODY ACCESS TO FILE");
        if (event->mask & IN_OPEN)
            log_mesg("FILE WAS OPEND");
        if (event->mask & IN_CLOSE_WRITE)
            log_mesg("FILE WAS CLOSED");
        if (event->mask &  IN_CLOSE_NOWRITE)
            log_mesg("FILE WAS CLOSED");
        if (event->mask &  IN_DELETE_SELF)
            log_mesg("FILE WAS DELETED");

        i += sizeof(struct inotify_event) + event->len;
        }
    }

    log_mesg("Stop watch to file");
    inotify_rm_watch( fd, wd );
    close( fd);

    log_mesg("Exit from track thread");
    pthread_exit(0);
}
