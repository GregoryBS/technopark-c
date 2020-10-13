#ifndef __LETTER_IO_H__
#define __LETTER_IO_H__

#include <stdlib.h>
#include "structs.h"

#define BUF_SIZE 20

typedef struct arr_t
{
    char *data;
    int len;
    int size;
    int space;
} string;

int read_text(char **text, char delimiter);

int read_letter(letter *ltr);

void free_mem(letter ltr);

#endif