#ifndef __FUNC_H__
#define __FUNC_H__

#include "structs.h"

#define TRUE 1
#define FALSE 0

/* Определение, является ли письмо спамом */
int is_spam(letter ltr, int *flag);

#endif