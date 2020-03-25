#include <time.h>
#include "lib.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if (argc != 3)
    {
        printf("Usage: main.out <dir> <str>\n");
        return ERR_ARG;
    }

    topfiles result = { { 0 }, { 0 } };
    clock_t t1 = clock();
    int rc = find_topfiles(&result, argv[1], argv[2]);
    clock_t t2 = clock();
    printf("Time of performing (mks): %ld\n", (long int) (t2 - t1));
    if (rc == OK)
        rc = write_results(&result);
    else
        printf("Error while finding %s in files of dir %s\n", argv[2], argv[1]);   
    return rc;
}