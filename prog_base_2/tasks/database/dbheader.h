#ifndef DBHEADER_H_INCLUDED
#define DBHEADER_H_INCLUDED

#include "teachers.h"
#include "sqlite3.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);
int db_countTeachers(db_t * self);
static void _fillTeacher (sqlite3_stmt * stmt, teacher_t t);
int db_getTeachersTask(db_t * self, int K, int P, teacher_t arr[]);
int db_insertTeacher(db_t * self, teacher_t teacher);
teacher_t db_getTeacherById(db_t * self, int id);
void teacher_update (db_t * self, teacher_t teacher);
void teacher_delete (db_t * self, teacher_t teacher);


#endif // DBHEADER_H_INCLUDED
