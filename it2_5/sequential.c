#include "sequential.h"

int byte_diff_count(int *counts, int n, char *mem, int size)
{
    if (!counts || n <= 0)
        return ERR_PARAM;
    if (!mem || size <= 0)
        return ERR_PARAM;
        
    int index = 0;
    for (int i = 1; i < size; i++)
    {
        index = fabs(mem[i - 1] - mem[i]);
        if (index < n)
            counts[index]++;
    }
    return OK;
}