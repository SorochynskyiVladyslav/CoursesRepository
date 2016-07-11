#define MAX_SIZE 30
#define MAX_NAME 20
#include "modules.h"

struct city {
    char* name;
    int x;
    int y;
};

struct list_s {
    struct city* city[MAX_SIZE];
    int count;
};

list_t list_new(void) {
    int i;
    list_t p = malloc(sizeof(struct list_s));
    for (i = 0; i <= MAX_SIZE; i++){
        p->city[i] = malloc(sizeof(struct city));
    }
    p->count = 0;
    return p;
}

list_t list_add(list_t p, int x, int y, const char * name, int index){
    int i;
    for (i = p->count; i > index; i--){
        p->city[i] = p->city[i - 1];
    }
    p->city[index]->name = name;
    p->city[index]->x = x;
    p->city[index]->y = y;
    p->count++;
    return p;
}

list_t list_remove(list_t p, int index){
    int i;
    for (i = index; i < p->count - 1; i++){
        p->city[i] = p->city[i + 1];
    }
    p->count--;
    return p;
}

double list_distance(list_t p, int index1, int index2){
    double dist = 0;
    dist = (double) sqrt(pow(p->city[index2]->x - p->city[index1]->x, 2) + pow(p->city[index2]->y - p->city[index1]->y, 2));
    printf("distance between %s and %s is %lf", p->city[index1]->name, p->city[index2]->name, dist);

    return dist;
}

void list_destroy (list_t p){
    int i;
    for (i = 0; i <= MAX_SIZE; i++){
        free (p->city[i]);
    }
    free(p);
}

int list_getsize(list_t p){
    return p->count;
}

void list_print(list_t p){
    int i = 0;
    puts("My list of cities");
    for (i = 0; i < p->count; i++){
        printf("%s (%i, %i)\n", p->city[i]->name, p->city[i]->x, p->city[i]->y);
    }
}
