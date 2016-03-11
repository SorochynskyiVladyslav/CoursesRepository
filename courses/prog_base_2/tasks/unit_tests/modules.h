#ifndef MODULES_H_INCLUDED
#define MODULES_H_INCLUDED

typedef struct list_s * list_t;

list_t list_new(void);
list_t list_add(list_t p, int x, int y, const char * name, int index);
list_t list_remove(list_t p, int index);
double list_distance(list_t p, int index1, int index2);
void list_destroy (list_t p);
int list_getsize(list_t p);

#endif // MODULES_H_INCLUDED
