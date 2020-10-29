#include "file.h"

int file_open(char *filename, char **filemem, int *filesize, int *fd)
{
    if (!filename || !filemem || !filesize || !fd)
        return ERR_PARAM;

    *fd = open(filename, O_RDONLY);
    if (*fd == -1)
        return ERR_IO;

    struct stat st = { 0 };
    stat(filename, &st);
    *filesize = st.st_size;
    *filemem = mmap(NULL, *filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, \
                    *fd, 0);
    if (*filemem == MAP_FAILED)
        return ERR_MEM;
    return OK;
}

int file_close(char *filemem, int filesize, int fd)
{
    int rc = OK;
    if (munmap(filemem, filesize) != 0)
       rc = ERR_MEM;

    close(fd);
    return rc; 
}

void diff_counts_print(const int *counts, int n)
{
    if (counts)
    {
        for (int i = 0; i < n; i++)
            printf("diff %d: %d\n", i, counts[i]);
    }
}