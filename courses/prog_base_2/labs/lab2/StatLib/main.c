#include "queue.h"

struct queue_s {
    int* elem;
    int size;
};

queue_t queue_new (void) {
    queue_t q;
    q = malloc(sizeof(struct queue_s));
    q->elem = malloc (sizeof(int)*10);
    q->size = 0;
    return q;
}

void queue_add (queue_t q, int value) {
    if (q->size == 10)
        return;
    q->elem[q->size] = value;
    q->size++;
}

int queue_remove (queue_t q) {
    if (q->size == 0)
        return 1;
    int i, val;
    val = q->elem[0];
    for (i = 0; i < q->size; i++){
        q->elem[i] = q->elem[i+1];
    }
    q->size--;
    return val;
}

int queue_getsize (queue_t q) {
    return q->size;
}

void queue_print(queue_t q) {
    int i;
    for (i = 0; i < q->size; i++) {
        printf("%i, ", q->elem[i]);
    }
    printf("\n");
}

void queue_free (queue_t q) {
    free(q->elem);
    free(q);
}
