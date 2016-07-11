#include "student.h"


struct student_s {
    char name[50];
    char surname[50];
    int age;
    float score;
};

student_t student_new (const char* nam, const char* surnam, int ag, float scor) {
    student_t self = malloc(sizeof(struct student_s));
    strcpy(self->name, nam);
    strcpy(self->surname, surnam);
    self->age = ag;
    self->score = scor;
    return self;
}

char* student_toString (student_t self) {
    char str[1000];
    char* res = str;
    sprintf(res, "Student\nName: %s\nSurname: %s\nAge: %i\nAverage score: %0.1f\n", self->name, self->surname, self->age, self->score);
    return res;
}


void student_free (student_t self) {
    free(self);
}
