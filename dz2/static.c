#include "lib.h"

int find_topfiles(topfiles *res, const char *dir_name, const char *str)
{
    if (!res || !dir_name || !str)
        return ERR_PARAM;

    int rc = OK;
    DIR *dp = opendir(dir_name);
    if (dp)
    {
        chdir(dir_name);
        struct dirent *dirp = NULL;
        int count = 0, flag = OK;
        while ((dirp = readdir(dp)))
        {
            flag = get_str_count(dirp->d_name, str, &count);
            if (flag == OK)
                change_result(res, dirp->d_name, count);
        }
        closedir(dp);
    }
    else
        rc = ERR_IO;
    return rc;
}