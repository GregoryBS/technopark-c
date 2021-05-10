#ifndef __SPORT_RESULT_IO_H__
#define __SPORT_RESULT_IO_H__

#include "structs.h"

typedef struct arr_t
{
    char *data;
    int len;
    int size;
    int space;
} string;

int free_mem(sport_result *results, const int n);

int read_results(sport_result **results, int *n);

int write_best(const sport_result *results, const int index[BEST_COUNT]);

#endif