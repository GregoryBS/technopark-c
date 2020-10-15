#ifndef __FUNC_H__
#define __FUNC_H__

#include <stdbool.h>
#include "structs.h"

/* Определение, является ли письмо спамом 
 * flag - флаг, будет установлен в true, если в письме найден спам
 */
int is_spam(letter *ltr, bool *flag);

#endif
