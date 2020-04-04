#include "static.h"

int find_topfiles(topfiles *res, dyn_array *f_names, const char *dir_name, \
                  const char *str)
{
    if (!res || !f_names || !dir_name || !str)
        return ERR_PARAM;

    char cur_dir[PATH_MAX] = {};
    readlink("/proc/self/exe", cur_dir, PATH_MAX);
    chdir(dir_name);
    int count = 0, flag = OK;
    for (int i = 0; i < f_names->len; i++)
    {
        flag = get_str_count(f_names->data[i], str, &count);
        if (flag == OK)
            change_result(res, f_names->data[i], count);
    }
    chdir(cur_dir);
    return OK;
}