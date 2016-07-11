#include "user.h"


struct user_s {
    char name[MAX_NAME];
};

user_t user_new (const char* name) {
    user_t self = malloc(sizeof(struct user_s));
    strcpy(self->name, name);
    return self;
}

void user_free (user_t self) {
    free(self);
}

char* user_getName (user_t self) {
    char* name = self->name;
    return name;
}

