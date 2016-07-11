#include "lab1head.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#define MAX_SIZE 10

struct post_s {
    int speed;
    int number;
    char* serial;
    record_status rstat;
};

struct postsystem_s {
    struct post * violation[MAX_SIZE];
    int count;
    system_status stat;
};

post_t post_new (int speed, int num, char* serial)  {
    post_t  po = malloc(sizeof(struct post_s));
    po->rstat = RECORD_OK;
    if (num < 0 || num > 9999)
        po->rstat = RECORD_WRONGNUMBER;
    if (speed <= 0)
        po->rstat = RECORD_WRONGSPEED;
    if (strlen(serial) != 4)
        po->rstat = RECORD_WRONGSERIAL;
    switch(po->rstat){
        case RECORD_OK:
            break;
        case RECORD_WRONGNUMBER:
            //puts("Error, wrong car number");
            return po;
        case RECORD_WRONGSERIAL:
            //puts("Error, wrong car serial");
            return po;
        case RECORD_WRONGSPEED:
            //puts("Error, wrong speed fixation");
            return po;
        default:
            puts("Error, unknown system status");
            break;
    }
    po->speed = speed;
    po->number = num;
    po->serial = serial;
    return po;
}

record_status post_getstatus(post_t po){
    return po->rstat;
}

postsystem_t postsystem_new(void) {
    int i;
    postsystem_t p = malloc(sizeof(struct postsystem_s));
    for (i = 0; i < MAX_SIZE; i++){
        p->violation[i] = malloc(sizeof(struct post_s));
    }
    p->count = 0;
    p->stat = SYSTEM_EMPTY;
    return p;
}

void postsystem_add(postsystem_t p, post_t po){
    if (post_getstatus(po) != RECORD_OK){
        puts("Error, can`t add an invalid record");
        return;
    }
    if (p->stat == SYSTEM_OVERFLOW){
        puts("Error, can`t fix more violations");
        return;
    }
    p->violation[p->count] = po;
    p->count++;
    p->stat = SYSTEM_OK;
    if (p->count == MAX_SIZE)
        p->stat = SYSTEM_OVERFLOW;
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
        printf("%3i", i);
        post_print(p->violation[i]);
        }
    printf("Total number of violations: %i\n", p->count);
    }

void post_print (post_t po) {
    printf(" Car: %s%4i Speed: %4i km/h\n", po->serial, po->number, po->speed);
}

void postsystem_destroy (postsystem_t p){
    int i;
    for (i = 0; i < MAX_SIZE; i++){
        free (p->violation[i]);
    }
    free(p);
}

system_status postsystem_getstatus (postsystem_t p){
    return p->stat;
}

int postsystem_getsize (postsystem_t p){
    return p->count;
}

int post_getNumber (post_t po){
    return po->number;
}

int post_getSpeed (post_t po){
    return po->speed;
}

char* post_getSerial (post_t po){
    return po->serial;
}
