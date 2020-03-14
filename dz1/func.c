#include "func.h"

void insert_index(const sport_result *arr, const int cur, int index[BEST_COUNT]);

int find_best(const sport_result *arr, const int n, int index[BEST_COUNT])
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

void insert_index(const sport_result *arr, const int cur, int idx[BEST_COUNT])
{
    int i = 0;
    int flag = TRUE;
    while (flag && i < BEST_COUNT)
    {
        if (idx[i] < 0 || arr[cur].checkpoints > arr[idx[i]].checkpoints || \
            (arr[cur].checkpoints == arr[idx[i]].checkpoints && \
            arr[idx[i]].time - arr[cur].time > EPS))
            flag = FALSE;
        else
            i++;
    }
    if (!flag)
    {
        if (idx[i] >= 0)
        {
            for (int j = BEST_COUNT - 1; j > i; j--)
                idx[j] = idx[j - 1];
        }
        idx[i] = cur;
    }
}