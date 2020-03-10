#include "func.h"

void insert_index(sport_result *arr, int cur, int *index);

int find_best(sport_result *arr, int n, int *index)
{
    if (!arr || !index)
        return ERR_PARAM;

    for (int i = 0; i < BEST_COUNT; i++)
        index[i] = -1;
    for (int i = 0; i < n; i++)
    {
        insert_index(arr, i, index);
    }
    return OK;
}

void insert_index(sport_result *arr, int cur, int *index)
{
    int i = 0;
    int flag = TRUE;
    while (flag && i < BEST_COUNT)
    {
        if (index[i] < 0 || arr[cur].checkpoints > arr[index[i]].checkpoints || arr[index[i]].time - arr[cur].time > EPS)
            flag = FALSE;
        else
            i++;
    }
    if (!flag)
    {
        if (index[i] >= 0)
        {
            for (int j = BEST_COUNT - 1; j > i; j--)
                index[j] = index[j - 1];
        }
        index[i] = cur;
    }
}