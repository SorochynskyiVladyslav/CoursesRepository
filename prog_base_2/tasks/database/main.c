#include "dbheader.h"

int main()
{
    const char * dbFile = "database.db";
    teacher_t tList[30];
    db_t * db = db_new(dbFile);

    int countAllTeachers = db_countTeachers(db);
    printf("Teachers total: %i\n\n", countAllTeachers);
    int filterSubjects = 2;
    int filterYears = 8;
    teacher_t arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = teacher_new();
    }
    int filtered = db_getTeachersTask(db, filterSubjects, filterYears, arr);
    printf("Teachers with subjects > %i or years > %i : %i\n Details:\n", filterSubjects, filterYears, filtered);
    for (int i = 0; i < filtered; i++) {
        teacher_print(arr[i]);
    }
    teacher_t t = teacher_new();
    t = db_getTeacherById(db, 4);
    puts("Got by id:");
    teacher_print(t);
    db_insertTeacher(db, t);
    t = db_getTeacherById(db, 6);
    for (int i = 0; i < 10; i++) {
       teacher_free(arr[i]);
    }
    teacher_free(t);
    return 0;
}
