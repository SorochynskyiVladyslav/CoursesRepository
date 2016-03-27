#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>
#include "threadheader.h"

typedef struct shared_s {
    char sChar;
    mutex_t * mu;
} shared_t;

void * Producer(void * args) {
    stack_t stack = (stack_t)args;
    srand(time(NULL));
    int num = rand() % 100;

    while (1) {
        mutex_lock(stack_returnMutex(stack));
        num = rand() % 100;
        stack_push(stack, num);
        mutex_unlock(stack_returnMutex(stack));
    }
    return NULL;
}

void * Consumer(void * args) {
    stack_t stack = (stack_t)args;
    while (1) {
        mutex_lock(stack_returnMutex(stack));
        printf("Deleted element %i\n", stack_pop(stack));
        mutex_unlock(stack_returnMutex(stack));
        Sleep(2000);
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));
    stack_t stack = stack_new();
    thread_t * setter1 = thread_create_args(Producer, stack);
    thread_t * writer = thread_create_args(Consumer, stack);
    thread_join(writer);  // wait here
    thread_free(setter1);
    thread_free(writer);
    stack_free(stack);
    return 0;
}
