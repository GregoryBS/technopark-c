#ifndef __EXTRA_FUNC_H__
#define __EXTRA_FUNC_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define OK 0
#define ERR_IO -1
#define ERR_MEM -2
#define ERR_PARAM -3
#define ERR_ARG -4
#define TOP_COUNT 5
#define PATH_MAX 4096

typedef struct files_t
{
    int count[TOP_COUNT];
    char *name[TOP_COUNT];
} topfiles;

typedef struct array_t
{
    char **data;
    int len;
    int size;
    int step;
} dyn_array;

int get_filenames_array(dyn_array *f_names, const char *dir_name);

int free_filenames_array(dyn_array *f_names);

int get_str_count(const char *file, const char *str, int *count);

int change_result(topfiles *res, const char *file, const int count);

int write_results(topfiles *res);

#endif