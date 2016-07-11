#ifndef TEACHERS_H_INCLUDED
#define TEACHERS_H_INCLUDED

#define MAX_NAME_SIZE 50
#define MAX_SURNAME_SIZE 100

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct teacher_s * teacher_t;
teacher_t teacher_new (void);
void teacher_free (teacher_t self);
void teacher_setName (teacher_t self, char* nam);
void teacher_setSurname (teacher_t self, char* surnam);
void teacher_setId (teacher_t self, int num);
void teacher_setRating (teacher_t self, double rat);
void teacher_setSubjects (teacher_t self, int sub);
void teacher_setYears (teacher_t self, int year);
void teacher_setBirthdate (teacher_t self, char* text);
void teacher_print (teacher_t self);


#endif // TEACHERS_H_INCLUDED
