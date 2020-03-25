#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include<sys/shm.h>
#include "lib.h"

typedef struct array_t
{
    char **data;
    int len;
    int size;
    int step;
} dyn_array;

int get_filenames_array(dyn_array *f_names, DIR *dp);

int run_process(topfiles *res, dyn_array *f_names, const char *str, \
               int begin, int size, struct sembuf *start, struct sembuf *end,\
               int sem_id);

int myround(float num);

int find_topfiles(topfiles *res, const char *dir_name, const char *str)
{
    if (!res || !dir_name || !str)
        return ERR_PARAM;

    int rc = OK;
    DIR *dp = opendir(dir_name);
    if (dp)
    {
        dyn_array filenames = { NULL, 0, 0, 25 };
        rc = get_filenames_array(&filenames, dp);
        if (rc == OK)
        {
            chdir(dir_name);
            struct sembuf start = { 0, -1, 0 };
	        struct sembuf end = { 0, 1, 0 };
            int perms = S_IRWXU | S_IRWXG | S_IRWXO;
            int fd = 0, sem_id = 0;
            topfiles *shbuf = NULL;
            if ((fd = shmget(IPC_PRIVATE, sizeof(topfiles), IPC_CREAT|perms))\
                == -1)
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
                    int begin = myround(i * (float) filenames.len / proc_n);
                    int size = myround((i + 1) * (float) filenames.len / \
                                       proc_n) - begin;
                    int pid = fork();
                    if (pid == 0)
                    {
                        rc = run_process(shbuf, &filenames, str, begin, \
                                         size, &start, &end, sem_id);
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
                *res = *shbuf;
                shmdt(shbuf);
                chdir("..");
            }
        }
        free(filenames.data);
        closedir(dp);
    }
    else
        rc = ERR_IO;
    return rc;
}

int myround(float num)
{
    return num + 0.5;
}

int get_filenames_array(dyn_array *f_names, DIR *dp)
{
    if (!f_names || !dp)
        return ERR_PARAM;

    int rc = OK;
    struct dirent *dirp = NULL;
    while (rc == OK && (dirp = readdir(dp)))
    {
        if (f_names->len == f_names->size)
        {
            char **tmp = (char**) realloc(f_names->data, (f_names->size + \
                                          f_names->step) * sizeof(char*));
            if (tmp)
            {
                f_names->data = tmp;
                f_names->size += f_names->step;
            }
            else
                rc = ERR_MEM;
        }
        if (rc == OK)
        {
            f_names->data[f_names->len] = dirp->d_name;
            f_names->len += 1;
        }
    }
    return rc;
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