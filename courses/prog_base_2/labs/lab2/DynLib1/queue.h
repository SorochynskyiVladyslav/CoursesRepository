#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue_s * queue_t;
queue_t queue_new (void);
void queue_add (queue_t q, int value);
int queue_remove (queue_t q);
int queue_getsize (queue_t q);
void queue_print(queue_t q);
void queue_free (queue_t q);


#endif // QUEUE_H_INCLUDED
