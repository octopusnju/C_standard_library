#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define TOTAL_PROCESS_NUM 10

//This array should be allocated in shared memory.
//Or every process get a copy of it and only have its own pid.
//pid_t ProcessID[TOTAL_PROCESS_NUM];
pid_t *ProcessID;

int rank;

void child_process() {
    printf("rank: %d, pid: %d, in child_process\n", rank, ProcessID[rank]);
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
            rank = crank;
            ProcessID[rank] = getpid();
            printf("rank: %d, pid: %d, REBORN\n", rank, ProcessID[rank]);
            child_process();
        }
    }
}

pid_t *alloc_pid_array_in_shm(int num)
{
    key_t shm_key = ftok("/", 0);
    int shm_fd = shmget(shm_key, sizeof(pid_t) * num, IPC_CREAT);
    void *shm_ptr = shmat(shm_fd, NULL, 0);
    return (pid_t *) shm_ptr;
}

int fork_child_process()
{
    int i = 1;
    while (i < TOTAL_PROCESS_NUM) {
        if (fork() == 0) {
            return i;
        } else {
            i++;
        }
    }
    return 0;
}

int main()
{
    ProcessID = alloc_pid_array_in_shm(TOTAL_PROCESS_NUM);//SHM
    rank = fork_child_process();//FORK PROCESS!!
    ProcessID[rank] = getpid();//LOG PID
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
