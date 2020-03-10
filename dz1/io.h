#ifndef __IO_H__
#define __IO_H__

#include "mem.h"

typedef struct arr_t
{
    char *data;
    int len;
    int size;
    int space;
} string;

int read_results(sport_result **arr, int *n);

void write_best(const sport_result *arr, const int *index);

#endif