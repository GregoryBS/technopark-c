#include "extra_func.h"

int write_results(topfiles *res)
{
    if (!res)
        return ERR_PARAM;

    if (res->count[0] > 0)
    {
        for (int i = 0; i < TOP_COUNT; i++)
            printf("%s %d\n", res->name[i], res->count[i]);
    }
    else
        printf("String not found.\n");
    return OK;
}

int change_result(topfiles *res, const char *file, const int count)
{
    if (!res || !file)
        return ERR_PARAM;

    int i = TOP_COUNT - 1, flag = OK;
    while (i >= 0 && flag == OK)
    {
        if (count <= res->count[i])
            flag = ERR_ARG;
        else
            i--;
    }
    i++;
    if (i >= 0)
    {
        for (int j = TOP_COUNT - 1; j > i; j--)
        {
            res->name[j] = res->name[j - 1];
            res->count[j] = res->count[j - 1];
        }
        res->name[i] = (char*) file;
        res->count[i] = count;
    }
    return OK;
}

int get_str_count(const char *file, const char *str, int *count)
{
    if (!file || !str || !count)
        return ERR_PARAM;

    int rc = OK;
    FILE *f = fopen(file, "r");
    if (f)
    {
        *count = 0;
        int n = strlen(str), k = 0;
        char c = '\0';
        while ((c = fgetc(f)) != EOF)
        {
            if (str[k] == c)
            {
                k++;
                if (k == n)
                {
                    *count += 1;
                    k = 0;
                }
            }
            else
                k = 0;
        }
        //printf("%s %d\n", file, *count);
        fclose(f);
    }
    else
        rc = ERR_IO;
    return rc;
}