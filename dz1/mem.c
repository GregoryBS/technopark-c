#include "mem.h"

int alloc_mem(sport_result **arr, const int n)
{
    if (!arr || n <= 0)
        return ERR_PARAM;

    int rc = OK;
    *arr = (sport_result*) malloc(n * sizeof(sport_result));
    if (*arr == NULL)
        rc = ERR_MEM;
    return rc;
}

void free_mem(sport_result *arr, const int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i].name);
    free(arr);
}