#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "user.h"

typedef struct file_s * file_t;

file_t file_new (const char* name, user_t user, int bytes);
void file_free (file_t self);
void file_print (file_t file);

char* file_getAuthor (file_t self);
user_t file_getUser (file_t self);
char* file_getName (file_t self);
int file_getBytes (file_t self);


#endif // FILE_H_INCLUDED
