#include "file.h"

struct file_s {
    char name[MAX_NAME];
    user_t author;
    int bytes;
};

file_t file_new (const char* name, user_t user, int bytes) {
    file_t self = malloc(sizeof(struct file_s));;
    strcpy(self->name, name);
    self->author = user;
    self->bytes = bytes;
    return self;
}

void file_free (file_t self) {
    free(self);
}

char* file_getAuthor (file_t self) {
    return  user_getName(self->author);
}

char* file_getName (file_t self) {
    char* name = self->name;
    return name;
}

int file_getBytes (file_t self) {
    return self->bytes;
}

void file_print (file_t file) {
    printf("File : %s\nAdded by: %s\nSize: %i bytes\n\n", file->name,
           user_getName(file->author),
           file->bytes);
}
