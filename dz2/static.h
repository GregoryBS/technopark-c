#ifndef __STATIC_H__
#define __STATIC_H__

#include "extra_func.h"

/* 
 * str - искомая строка запроса
 * dir_name - имя директории с файлами для поиска
 * f_names - указатель на структуру, хранящей все имена файлов для поиска
 * res - результат в виде структуры из массивов имён файлов и кол-в str в них
 * Функция открывает все файлы в директории и посимвольно ищет вхождения стро-
 * ки, формируя результат внутри структуры
 */
int find_topfiles(topfiles *res, dyn_array *f_names, const char *dir_name, \
                  const char *str);

#endif