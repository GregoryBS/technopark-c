#include <time.h>
#include <dlfcn.h>
#include "file.h"
#include "sequential.h"

#define NANOS 1e9

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if (argc != 2)
    {
        printf("Usage: main.out <filename>\n");
        return ERR_ARG;
    }

    int fd = -1, file_size = 0;
    char *file = NULL;
    int rc = file_open(argv[1], &file, &file_size, &fd);
    if (rc != OK)
    {
        printf("Impossible to open file: %s\n", argv[1]);
        return rc;
    }

    int *result = calloc(N + 1, sizeof(int));
    if (result)
    {
        struct timespec t1 = { 0 }, t2 = { 0 };
        clock_gettime(CLOCK_REALTIME, &t1);
        rc = byte_diff_count(result, N + 1, file, file_size);
        clock_gettime(CLOCK_REALTIME, &t2);
        printf("Time of sequential perform (s): %.3f\n", \
                t2.tv_sec - t1.tv_sec + (t2.tv_nsec - t1.tv_nsec) / NANOS);
        if (rc == OK)
            diff_counts_print(result, N + 1);

        void *library = dlopen("libparallel.so", RTLD_LAZY);
        if (library)
        {
            int (*func)(int*, int, const char*, int) = NULL;
            func = dlsym(library, "byte_diff_count");
            clock_gettime(CLOCK_REALTIME, &t1);
            rc = func(result, N + 1, file, file_size);
            clock_gettime(CLOCK_REALTIME, &t2);
            printf("Time of parallel perform (s): %.3f\n", \
                   t2.tv_sec - t1.tv_sec + (t2.tv_nsec - t1.tv_nsec) / NANOS);
            if (rc == OK)
                diff_counts_print(result, N + 1);
            dlclose(library);
        }
        else
            printf("Cannot open dynamic library!\n");
        free(result);
    }
    
    rc = file_close(file, file_size, fd);
    if (rc != OK)
        printf("Error while closing file: %s\n", argv[1]);
    return rc;
}
