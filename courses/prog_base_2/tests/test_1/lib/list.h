#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "stock.h"

typedef struct list_s * list_t;

int list_size(list_t list);
good_t list_getGood (list_t list, int pos);
good_t list_change(list_t list, good_t data, int pos);
good_t list_del(list_t list, int pos);
void list_add(list_t list, good_t data, int pos);
list_t list_new();

#endif // LIST_H_INCLUDED

