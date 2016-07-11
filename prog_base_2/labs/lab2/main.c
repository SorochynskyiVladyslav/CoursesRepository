#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "dynamicLibs.h"

const char* chooseLib (void);

int main()
{
    queue_t queue = queue_new();
    dynamic_t * dll = dynamic_init(chooseLib ());
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->chk) {
        printf("Can't get check function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    srand(time(NULL));

    int i = 0;
    for (i = 0; i < 7; i++){
        queue_add(queue, rand() % 5);
    }
    queue_print(queue);
    if(dll->chk(queue) == 1) {
        dll->react();
    }
    queue_free(queue);
    return 0;
}

const char* chooseLib (void) {
    puts ("Enter number of library you want to use");
    puts ("DynLib1 >> 1");
    puts ("DynLib2 >> 2");
    printf("enter your choise >> ");
    int num;
    scanf("%i", &num);
    if (num == 1)
        return "DynLib1.dll";
    if (num == 2)
        return "DynLib2.dll";
}


