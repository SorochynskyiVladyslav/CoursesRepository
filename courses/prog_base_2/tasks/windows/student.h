#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct student_s * student_t;

student_t student_new (const char* nam, const char* surnam, int ag, float scor);
void student_free (student_t self);
char* student_toString (student_t self);


#endif // STUDENT_H_INCLUDED
