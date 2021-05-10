#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct result_t 
{
    int number;
    int checkpoints;
    char *name;
    float time;
} sport_result;

#define OK 0
#define ERR_IO -1
#define ERR_MEM -2
#define ERR_PARAM -3
#define EPS 1e-6
#define BEST_COUNT 10

#endif