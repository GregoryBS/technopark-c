#ifndef __SEQUENTIAL_H__
#define __SEQUENTIAL_H__

#include "headers.h"

/* 
 * Заполнение массива counts кол-вом пар байт, отличающихся
 * на 0, 1, ... (n - 1), памяти в указателе mem размером size. 
 */
int byte_diff_count(int *counts, int n, char *mem, int size);

#endif
