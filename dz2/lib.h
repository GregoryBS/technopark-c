#ifndef __LIB_H__
#define __LIB_H__

#include <dirent.h>
#include <unistd.h>
#include "extra_func.h"

/* 
 * str - искомая строка запроса
 * dir_name - имя директории с файлами для поиска
 * res - результат в виде структуры из массивов имён файлов и кол-в str в них
 * Функция открывает все файлы в директории и посимвольно ищет вхождения стро-
 * ки, формируя результат внутри структуры
 */
int find_topfiles(topfiles *res, const char *dir_name, const char *str);

#endif