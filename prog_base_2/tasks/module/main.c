#include <stdio.h>
#include <stdlib.h>
#include "modules.h"

int main()
{
    int a;
    list_t p = list_new();
    printf("list size is %i\n", list_getsize(p));
    p = list_add(p, 5, 6, "Kyiv", 0);
    p = list_add(p, 8, 2, "Lviv", 1);
    p = list_add(p, 1, 4, "Chernigiv", 2);
    p = list_add(p, 3, 6, "Dnipropetrovsk", 3);
    p = list_add(p, 9, 8, "Donetsk", 4);
    list_print(p);
    ("now i`ll remove element 3");
    p = list_remove(p, 3);
    list_print(p);
    list_distance(p, 1, 3);
    list_destroy (p);
    return 0;
}
