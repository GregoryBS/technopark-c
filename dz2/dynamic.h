#ifndef __DYNAMIC_H__
#define __DYNAMIC_H__

#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include "extra_func.h"

/* 
 * str - искомая строка запроса
 * dir_name - имя директории с файлами для поиска
 * f_names - указатель на структуру, хранящей все имена файлов для поиска
 * res - результат в виде структуры из массивов имён файлов и кол-в str в них
 * Функция открывает все файлы в директории и посимвольно ищет вхождения стро-
 * ки, формируя результат внутри структуры
 */
int find_topfiles_p(topfiles *res, dyn_array *f_names, const char *dir_name, \
                  const char *str);

int run_process(topfiles *res, dyn_array *f_names, const char *str, \
               int begin, int size, struct sembuf *start, struct sembuf *end,\
               int sem_id);

int myround(float num);

#endif