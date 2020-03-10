#ifndef __MEM_H__
#define __MEM_H__

#include "structs.h"

int alloc_mem(sport_result **arr, const int n);

void free_mem(sport_result *arr, const int n);

#endif