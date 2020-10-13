#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdio.h>
#include <string.h>

typedef struct letter_t 
{
    char *sender;
    char *receiver;
    char *theme;
    char *text;
} letter;

#define OK 0
#define ERR_IO -1
#define ERR_MEM -2
#define ERR_PARAM -3

#define SPAM "швейцарские часы"

#endif