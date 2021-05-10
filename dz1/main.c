#include "sport_result_io.h"
#include "func.h"

int main(void)
{
    setbuf(stdout, NULL);
    sport_result *arr = NULL;
    int count = 0;
    int rc = read_results(&arr, &count);
    if (rc == OK)
    {
        int best_index[BEST_COUNT] = { 0 };
        rc = find_best(arr, count, best_index);
        if (rc == OK)
            write_best(arr, best_index);
        else
            printf("Cannot find best %d teams\n", BEST_COUNT);
        free_mem(arr, count);
    }
    return rc;
}
    