#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#define MAX_NAME 100

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct user_s * user_t;

user_t user_new (const char* name);
void user_free (user_t self);
char* user_getName (user_t self);

#endif // USER_H_INCLUDED
