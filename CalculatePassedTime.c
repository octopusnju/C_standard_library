#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    struct timeval before, after;
    gettimeofday(&before, NULL);

    usleep(555000); //the executing code before

    gettimeofday(&after, NULL);

#if 1
    int delta_time_in_usec = (after.tv_sec - before.tv_sec) * 1000000 + (after.tv_usec - before.tv_usec);
    printf("time passed: %d usec.\n", delta_time_in_usec);
#else
    int delta_sec = after.tv_sec - before.tv_sec;
    int delta_usec = after.tv_usec - before.tv_usec;
    if (delta_usec < 0)
    {
        delta_sec -= 1;
        delta_usec += 1000000;
    }
    printf("time passed: %d sec, %d usec.\n", delta_sec, delta_usec);
#endif
    
    return 0;
}
