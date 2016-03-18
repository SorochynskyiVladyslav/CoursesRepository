#ifndef LAB1HEAD_H_INCLUDED
#define LAB1HEAD_H_INCLUDED

typedef struct postsystem_s * postsystem_t;
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
record_status postsystem_add(postsystem_t p, int speed, int num, char * serial);
void postsystem_remove(postsystem_t p, int index);
void postsystem_print (postsystem_t p);
void postsystem_destroy (postsystem_t p);
system_status postsystem_getstatus (postsystem_t p);
int postsystem_getsize (postsystem_t p);
int testSystem (void);



#endif // LAB1HEAD_H_INCLUDED
