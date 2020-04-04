#include "dynamic.h"

int find_topfiles(topfiles *res, dyn_array *f_names, const char *dir_name, \
                  const char *str)
{
    if (!res || !f_names || !dir_name || !str)
        return ERR_PARAM;

    int rc = OK;
    char cur_dir[PATH_MAX] = {};
    readlink("/proc/self/exe", cur_dir, PATH_MAX);        
    chdir(dir_name);
    struct sembuf start = { 0, -1, 0 };
	struct sembuf end = { 0, 1, 0 };
    int perms = S_IRWXU | S_IRWXG | S_IRWXO;
    int fd = 0, sem_id = 0;
    topfiles *shbuf = NULL;
    if ((fd = shmget(IPC_PRIVATE, sizeof(topfiles), IPC_CREAT|perms)) == -1)
        rc = ERR_MEM;
    if ((shbuf = (topfiles*) shmat(fd, 0, 0)) == (topfiles*) -1)
        rc = ERR_MEM;
    if ((sem_id = semget(IPC_PRIVATE, 1, perms)) == -1)
        rc = ERR_MEM;
    if (rc == OK)
    {
        semctl(sem_id, 0, SETVAL, 1);
        int proc_n = get_nprocs();
        for (int i = 0; i < proc_n; i++)
        {
            int begin = myround(i * (float) f_names->len / proc_n);
            int size = myround((i + 1) * (float) f_names->len / proc_n) - \
                               begin;
            int pid = fork();
            if (pid == 0)
            {
                rc = run_process(shbuf, f_names, str, begin, size, &start, \
                                 &end, sem_id);
                exit(rc);
            }
        }

        int status = 0;
        for (int i = 0; i < proc_n; i++)
        {
            wait(&status);
            if (rc == OK && !WIFEXITED(status))
                rc = ERR_IO;
        }

        if (rc == OK)
            *res = *shbuf;
        shmdt(shbuf);
    }
    chdir(cur_dir);
    return rc;
}

int myround(float num)
{
    return num + 0.5;
}

int run_process(topfiles *res, dyn_array *f_names, const char *str, \
               int begin, int size, struct sembuf *start, struct sembuf *end,\
               int sem_id)
{
    if (!res || !f_names || !str || begin < 0 || size <= 0 || !end || !start)
        return ERR_PARAM;

    int flag = 0, count = 0;
    for (int i = 0; i < size; i++)
    {
        flag = get_str_count(f_names->data[i + begin], str, &count);
        if (flag == OK)
        {
            semop(sem_id, start, 1);
            change_result(res, f_names->data[i + begin], count);
            semop(sem_id, end, 1);
        }
    }
    return OK;
}