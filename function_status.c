#include <stdio.h> //sprintf, fprintf, fopen, fclose
#include <unistd.h> //pid_t, getpid(), usleep()
#include <time.h> //struct tm, time, localtime
#include <sys/time.h> //struct timeval, gettimeofday
#include <pthread.h> //pthread*, -lpthread

#include "function_status.h"

static char *time_fmt = "%04d%02d%02d-%02d:%02d:%02d-%06dus";
static char *file_str = FILE_STR;//"function_status.log";

static pthread_mutex_t lock;

void get_time_str(char time_str[])
{
    time_t t;
    time(&t);
    struct tm *tp = localtime(&t);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    sprintf(time_str, time_fmt, tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, \
            tp->tm_hour, tp->tm_min, tp->tm_sec, tv.tv_usec);
}

void function_status(const char *func)
{
    pthread_mutex_lock(&lock);
    FILE *fp = fopen(file_str, "a");
    if (NULL == fp) {
        pthread_mutex_unlock(&lock);
        return;
    }

    char time_str[30];
    get_time_str(time_str);
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    fprintf(fp, "%s, ", time_str);
    fprintf(fp, "PID:%05u, ", pid);
    fprintf(fp, "TID:%010lu, ", tid);
    fprintf(fp, "FUNC:%s", func);
    fprintf(fp, "\n");

    fclose(fp);
    pthread_mutex_unlock(&lock);
}
