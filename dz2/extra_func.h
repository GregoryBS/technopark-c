#ifndef __EXTRA_FUNC_H__
#define __EXTRA_FUNC_H__

#include <stdio.h>
#include <string.h>

#define OK 0
#define ERR_IO -1
#define ERR_MEM -2
#define ERR_PARAM -3
#define ERR_ARG -4
#define TOP_COUNT 5

typedef struct files_t
{
    int count[TOP_COUNT];
    char *name[TOP_COUNT];
} topfiles;

int get_str_count(const char *file, const char *str, int *count);

int change_result(topfiles *res, const char *file, const int count);

int write_results(topfiles *res);

#endif