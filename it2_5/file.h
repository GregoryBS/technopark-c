#ifndef __FILE_H__
#define __FILE_H__

#include <sys/stat.h>
#include "headers.h"

int file_open(char *filename, char **filemem, int *filesize, int *fd);

int file_close(char *filemem, int filesize, int fd);

void diff_counts_print(const int *counts, int n);

#endif
