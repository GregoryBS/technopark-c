#include "parallel.h"

int myround(float num)
{
    return num + 0.5;
}

int run_process(char *mem, int begin, int end, int *counts, int n)
{
    if (!mem || begin < 0 || end < begin)
        return ERR_PARAM;
    if (!counts || n <= 0)
        return ERR_PARAM;

    int index = 0;
    for (int i = begin + 1; i < end; i++)
    {
        index = fabs(mem[i - 1] - mem[i]);
        if (index < n)
            counts[index]++;
    }
    return OK;
}

int byte_diff_count(int *counts, int n, char *mem, int size)
{
    if (!counts || n <= 0)
        return ERR_PARAM;
    if (!mem || size <= 0)
        return ERR_PARAM;

    sem_t *mutex = NULL;
    if ((mutex = sem_open(MUTEX, O_CREAT, PERMS, 1)) == SEM_FAILED)
        return ERR_MEM;

    int shared_size = n * sizeof(int);
    int *shared = mmap(NULL, shared_size, PROT_READ | PROT_WRITE, \
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared == MAP_FAILED)
        return ERR_MEM;
    for (int i = 0; i < n; i++)
        shared[i] = 0;

    int rc = OK;
    int proc_count = get_nprocs();
    int begin = 0, end = 1;
    for (int i = 1; i <= proc_count; i++)
    {
        begin = end - 1;
        end = size - myround((proc_count - i) * (float) size / proc_count);
        int pid = fork();
        if (pid == 0)
        {
            int *diffs = calloc(n, sizeof(int));
            if (!diffs)
                exit(ERR_MEM);
            rc = run_process(mem, begin, end, diffs, n);
            if (rc == OK)
            {
                sem_wait(mutex);
                for (int i = 0; i < n; i++)
                    shared[i] += diffs[i];
                sem_post(mutex);
            }
            free(diffs);
            exit(rc);
        }
    }

    int status = 0;
    for (int i = 0; i < proc_count; i++)
    {
        wait(&status);
        if (rc == OK && !WIFEXITED(status))
            rc = ERR_PROC;
    }
    if (rc == OK)
    {
        for (int i = 0; i < n; i++)
            counts[i] = shared[i];
    }

    munmap(shared, shared_size);
    sem_unlink(MUTEX);
    return rc;
}
