#include "lab1head.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#define MAX_SIZE 8

struct post {
    int speed;
    int number;
    char* serial;
};

struct postsystem_s {
    struct post * violation[MAX_SIZE];
    int count;
    system_status stat;
};

postsystem_t postsystem_new(void) {
    int i;
    postsystem_t p = malloc(sizeof(struct postsystem_s));
    for (i = 0; i < MAX_SIZE; i++){
        p->violation[i] = malloc(sizeof(struct post));
    }
    p->count = 0;
    p->stat = SYSTEM_EMPTY;
    return p;
}

record_status postsystem_add(postsystem_t p, int speed, int num, char * serial){
    record_status rstat = RECORD_OK;
    if (num < 0 || num > 9999)
        rstat = RECORD_WRONGNUMBER;
    if (speed <= 0)
        rstat = RECORD_WRONGSPEED;
    if (strlen(serial) != 4)
        rstat = RECORD_WRONGSERIAL;
    switch(rstat){
        case RECORD_OK:
            break;
        case RECORD_WRONGNUMBER:
            puts("Error, wrong car number");
            return rstat;
        case RECORD_WRONGSERIAL:
            puts("Error, wrong car serial");
            return rstat;
        case RECORD_WRONGSPEED:
            puts("Error, wrong speed fixation");
            return rstat;
        default:
            puts("Error, unknown system status");
            break;
    }
    if (p->stat == SYSTEM_OVERFLOW){
        puts("Error, can`t fix more violations");
        return rstat;
    }
    p->violation[p->count]->speed = speed;
    p->violation[p->count]->number = num;
    p->violation[p->count]->serial = serial;
    p->count++;
    p->stat = SYSTEM_OK;
    if (p->count == MAX_SIZE)
        p->stat = SYSTEM_OVERFLOW;
    return rstat;
}

void postsystem_remove(postsystem_t p, int index){
    if (p->stat == SYSTEM_EMPTY){
        puts("No more violations to deal with");
        return;
    }
    int i = index;
    for (i = index; i < p->count - 1; i++){
        p->violation[i] = p->violation[i + 1];
    }
    p->count--;
    if (p->count == 0){
        p->stat = SYSTEM_EMPTY;
    }
}

void postsystem_print (postsystem_t p){
    int i;
    for (i = 0; i < p->count; i++){
        printf("%3i Car: %s%4i Speed: %4i km/h\n", i, p->violation[i]->serial, p->violation[i]->number, p->violation[i]->speed);
        }
    printf("Total number of violations: %i\n", p->count);
    }

void postsystem_destroy (postsystem_t p){
    int i;
    for (i = 0; i < MAX_SIZE; i++){
        free (p->violation[i]);
    }
    free(p);
}

system_status postsystem_getstatus (postsystem_t p){
    switch (p->stat){
        case SYSTEM_EMPTY:
            puts("System contains no violations");
            break;
        case SYSTEM_OVERFLOW:
            puts("System contains maximum amount of violations");
            break;
        case SYSTEM_OK:
            puts("System is OK");
            break;
        default:
            puts("Error, can`t recognise system`s status");
            break;
    }
    return p->stat;
}

int postsystem_getsize (postsystem_t p){
    return p->count;
}


