#include <time.h>
#include <dlfcn.h>
#include "static.h"
#include "dynamic.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if (argc != 3)
    {
        printf("Usage: main.out <dir> <str>\n");
        return ERR_ARG;
    }

    dyn_array filenames = { NULL, 0, 0, 25 };
    int rc = get_filenames_array(&filenames, argv[1]);
    if (rc == OK)
    {
        topfiles result = { { 0 }, { 0 } };
        clock_t t1 = clock();
        int rc1 = find_topfiles(&result, &filenames, argv[1], argv[2]);
        clock_t t2 = clock();
        printf("Time of serial performing (mks): %ld\n", (long int) (t2 - t1));
        if (rc1 == OK)
            rc1 = write_results(&result);
        else
            printf("Error while finding %s in files of dir %s\n", argv[2], \
                argv[1]);   

        int rc2 = OK;
        /*void *library = dlopen("lib_parallel.so", RTLD_LAZY);
        if (library)
        {
            int (*func)(topfiles*,dyn_array*,const char*,const char*) =  NULL;
            func = dlsym(library, "find_topfiles");
            t1 = clock();
            rc2 = func(&result, &filenames, argv[1], argv[2]);
            t2 = clock();
            printf("Time of performing (mks): %ld\n", (long int) (t2 - t1));
            if (rc2 == OK)
                rc2 = write_results(&result);
            else
                printf("Error while finding %s in files of dir %s\n", \
                       argv[2], argv[1]); 
            dlclose(library);
        }
        else
            rc2 = ERR_MEM;*/
        t1 = clock();
        rc2 = find_topfiles_p(&result, &filenames, argv[1], argv[2]);
        t2 = clock();
        printf("Time of parallel performing (mks): %ld\n", (long int) (t2 - t1));
        if (rc2 == OK)
            rc2 = write_results(&result);
        else
            printf("Error while finding %s in files of dir %s\n", \
                       argv[2], argv[1]);

        free_filenames_array(&filenames);
        rc = rc1 || rc2;
    }
    else
        printf("Error while opening dir %s\n", argv[1]);
    return rc;
}