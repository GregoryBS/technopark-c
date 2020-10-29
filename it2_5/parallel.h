#ifndef __PARALLEL_H__
#define __PARALLEL_H__

#include <semaphore.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include "headers.h"

#define MUTEX "my_mutex"
#define PERMS 644

/* 
 * Заполнение массива counts кол-вом пар байт, отличающихся
 * на 0, 1, ... (n - 1), памяти в указателе mem размером size. 
 */
int byte_diff_count(int *counts, int n, char *mem, int size);

#endif
