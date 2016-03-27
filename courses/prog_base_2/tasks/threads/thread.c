#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threadheader.h"
#include <windows.h>

struct stack_s {
    int* arr;
    int size;
    status stat;
    mutex_t * mu;
};

stack_t stack_new (void) {
    stack_t p = malloc(sizeof(struct stack_s));
    p->arr = malloc(sizeof(int)*5);
    p->stat = STACK_OK;
    p->size = 0;
    p->mu = mutex_new();
    return p;
}

mutex_t* stack_returnMutex (stack_t s){
    return s->mu;
}

void stack_push (stack_t p, int element) {
    if (p->size == 5 || p->stat == STACK_OVERFLOW){
        p->size = 4;
        p->stat = STACK_OVERFLOW;
        return;
    }
    p->arr[p->size] = element;
    p->size++;
}


void stack_free (stack_t s){
    free(s->arr);
    free(s);
    mutex_free(s->mu);
}


int stack_pop (stack_t p) {
    if (p->size == 0){
        return;
    }
    int val = p->arr[p->size];
    p->size--;
    return val;
}
