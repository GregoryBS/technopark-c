#ifndef __DYNAMIC_H__
#define __DYNAMIC_H__

#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>

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

#endif