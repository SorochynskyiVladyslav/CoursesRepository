#include "head.h"


struct teacher_s {
    char name[100];
    char surname[100];
    struct tm birthdate;
    int since;
    double rating;
    char chair[100];
    char faculty[100];
};

teacher_t teacher_new (void) {
    teacher_t t = malloc (sizeof(struct teacher_s));
    return t;
}

void teacher_remove (teacher_t t) {
    free(t);
}

void teacher_print (teacher_t t) {
    printf("Teacher: \n %s %s\n Info:\n Born on: %i-%i-%i\n Teaches at %s faculty (%s chair) since %i\n Rating among students %.1f\n\n",
           t->name, t->surname, t->birthdate.tm_year + 1900, t->birthdate.tm_mon + 1, t->birthdate.tm_mday,
            t->faculty, t->chair, t->since, t->rating);
}

void teacher_setName (teacher_t t, char* name) {
    strcat(t->name, name);
}

void teacher_setSurname (teacher_t t, char* surname) {
    strcat(t->surname, surname);
}

void teacher_setBirthdate (teacher_t t, char* content) {
    char* str = content;
    time_t rawtime;
    time( &rawtime );
    struct tm* temp;
    temp = localtime( &rawtime );
    t->birthdate = *temp;
    t->birthdate.tm_year = atoi(str) - 1900;
    while(*str != '-'){
        str++;
    }
    str++;
    t->birthdate.tm_mon = atoi(str) - 1;
    while(*str != '-'){
        str++;
    }
    str++;
    t->birthdate.tm_mday = atoi(str);
}

void teacher_setFaculty (teacher_t t, xmlNode * xJ) {
    xmlNode * xChair = xJ;
    xmlNode * xFac = xChair->children->next;
    char * fac = xmlNodeGetContent(xFac);
    strcat(t->faculty, fac);
}

void teacher_setChair (teacher_t t, xmlNode * xJ) {
    xmlNode * xChair = xJ;
    char * name = xmlGetProp(xChair, "name");
    strcat(t->chair, name);
}

void teacher_setSince (teacher_t t, char* content) {
    int since = 0;
    since = atoi(content);
    t->since = since;
}

void teacher_setRating (teacher_t t, char* content) {
    double rating = atof(content);
    t->rating = rating;
}
