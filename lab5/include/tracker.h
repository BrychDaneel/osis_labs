#include <pthread.h>


pthread_t start_track(const char * track_file);

void stop_track(pthread_t track_thread);
