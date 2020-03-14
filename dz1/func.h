#ifndef __FUNC_H__
#define __FUNC_H__

#include "structs.h"

#define TRUE 1
#define FALSE 0

/* Проход по массиву результатов и формирование массива index индексов
   лучших результатов */
int find_best(const sport_result *arr, const int n, int index[BEST_COUNT]);

#endif