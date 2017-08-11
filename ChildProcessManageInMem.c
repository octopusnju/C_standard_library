#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define TOTAL_PROCESS_NUM 10

pid_t ProcessID[TOTAL_PROCESS_NUM];

int rank;

void child_process() {
    printf("rank: %d, pid: %d, in child_process\n", rank, getpid());
    usleep((rand() + rank*10) % 100 * 10000);
    char *p = NULL;
    *p = 1;
}

pid_t wait_child_pid()
{
    int status;
    return waitpid(-1, &status, 0);
}

int match_child_rank(pid_t cpid)
{
    int i = 1;
    while (i < TOTAL_PROCESS_NUM)
    {
        if (cpid == ProcessID[i])
        {
            return i;
        }
        i++;
    }
    return 0;
}

void manage_process()
{
    printf("rank: %d, pid: %d, in manage_process\n", rank, ProcessID[rank]);
    while (1)
    {
        pid_t cpid = wait_child_pid();
        int crank = match_child_rank(cpid);
        if (crank == 0)
            continue;

        printf("rank: %d, pid: %d, CATCH\n", crank, cpid);

        if((cpid = fork()) == 0)
        {
            sleep(1);
            rank = crank;
            child_process();
        }
        else
        {
            ProcessID[crank] = cpid;
            printf("rank: %d, pid: %d, REBORN\n", crank, ProcessID[crank]);
        }

    }
}

int fork_and_log_pid()
{
    int i = 1;
    pid_t cpid;
    while (i < TOTAL_PROCESS_NUM) {
        cpid = fork();
        if (cpid == 0) {
            sleep(1);
            return i;
        } else {
            ProcessID[i] = cpid;
            i++;
        }
    }
    return 0;
}

int main()
{
    rank = fork_and_log_pid(); //only log in father process
    switch (rank) {
        case 0:
            manage_process();
            break;
        default:
            child_process();
            break;
    }
    return 0;
}
