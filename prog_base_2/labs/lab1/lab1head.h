#ifndef LAB1HEAD_H_INCLUDED
#define LAB1HEAD_H_INCLUDED

typedef struct postsystem_s * postsystem_t;
typedef struct post_s * post_t;

typedef enum record_status{
    RECORD_OK,
    RECORD_WRONGSPEED,
    RECORD_WRONGNUMBER,
    RECORD_WRONGSERIAL,
} record_status;

typedef enum system_status{
    SYSTEM_OK,
    SYSTEM_EMPTY,
    SYSTEM_OVERFLOW,
} system_status;

postsystem_t postsystem_new(void);
void postsystem_add(postsystem_t p, post_t po);
void postsystem_remove(postsystem_t p, int index);
void postsystem_print (postsystem_t p);
void postsystem_destroy (postsystem_t p);
system_status postsystem_getstatus (postsystem_t p);
int postsystem_getsize (postsystem_t p);
int testSystem (void);

void post_print (post_t po);
int post_getNumber (post_t po);
int post_getSpeed (post_t po);
char* post_getSerial(post_t po);
record_status post_getstatus(post_t po);


#endif // LAB1HEAD_H_INCLUDED
