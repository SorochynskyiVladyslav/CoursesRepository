#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <locale.h>
#include <time.h>

#define TEXT_MAX_SIZE 1000
#define LINE_MAX_SIZE 100

typedef struct teacher_s * teacher_t;

teacher_t teacher_new (void);
void teacher_remove (teacher_t t);
void teacher_print (teacher_t t);

void teacher_setName (teacher_t t, char* name);
void teacher_setSurname (teacher_t t, char* surname);
void teacher_setBirthdate (teacher_t t, char* content);
void teacher_setFaculty (teacher_t t, xmlNode * xJ);
void teacher_setChair (teacher_t t, xmlNode * xJ);
void teacher_setSince (teacher_t t, char* content);
void teacher_setRating (teacher_t t, char* content);
teacher_t ReadXml (teacher_t t[], int amount, char text[]);





#endif // HEAD_H_INCLUDED
