#include "dbheader.h"
#include "teachers.h"

struct db_s {
    sqlite3 * db;
};

db_t * db_new(const char * dbFile) {
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self) {
    sqlite3_close(self->db);
    free(self);
}


int db_countTeachers(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Teacher;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

static void _fillTeacher (sqlite3_stmt * stmt, teacher_t t) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    double rating = sqlite3_column_double(stmt, 3);
    int subjects = sqlite3_column_int(stmt, 4);
    int years = sqlite3_column_int(stmt, 5);
    const unsigned char* text = sqlite3_column_text(stmt, 6);
    teacher_setId(t, id);
    teacher_setName(t, name);
    teacher_setSubjects(t, subjects);
    teacher_setSurname(t, surname);
    teacher_setYears(t, years);
    teacher_setRating(t, rating);
    teacher_setBirthdate(t, text);
}

int db_getTeachersTask(db_t * self, int K, int P, teacher_t arr[]) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Teacher WHERE subjects > ? OR years > ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select teachers\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillTeacher(stmt, arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}

struct teacher_s {
    int id;
    char name[MAX_NAME_SIZE];
    char surname[MAX_SURNAME_SIZE];
    double rating;
    int subjects;
    int years;
    char birthdate[11];
};

teacher_t teacher_new (void) {
    teacher_t self = malloc(sizeof(struct teacher_s));
    return self;
}

void teacher_free (teacher_t self) {
    free(self);
}

void teacher_setName (teacher_t self, char* nam) {
    strcat(self->name, nam);
}

void teacher_setSurname (teacher_t self, char* surnam) {
    strcat(self->surname, surnam);
}

void teacher_setId (teacher_t self, int num) {
    self->id = num;
}

void teacher_setRating (teacher_t self, double rat) {
    self->rating = rat;
}

void teacher_setSubjects (teacher_t self, int sub) {
    self->subjects = sub;
}

void teacher_setYears (teacher_t self, int year) {
    self->years = year;
}

void teacher_setBirthdate (teacher_t self, char* text) {
    strcat(self->birthdate, text);
}

void teacher_print (teacher_t self) {
    char* name = self->name;
    name += 3;
    char* birth = self->birthdate;
    while (isdigit(*birth) == 0)
        birth++;
    printf("\tTeacher: %s %s\n", name, self->surname);
    printf("\tsubjects: %i\n", self->subjects);
    printf("\trating: %.1f\n", self->rating);
    printf("\tteaching: %3i years\n", self->years);
    printf("\tbirthdate: %11s\n\n", birth);
}


int db_insertTeacher(db_t * self, teacher_t teacher) {
    int newStudentId = -1;
    int rc = 0;
    sqlite3_stmt * stmt = NULL;
    int count = db_countTeachers(self);
    count++;
    const char * sqlQuery = "insert into Teacher (id, name, surname, rating, subjects, years, birthdate) "
    "values (?, ?, ?, ?, ?, ?, ?);";
    char* name = teacher->name;
    name+=3;
    char* surname = teacher->surname;
    char* birthdate = teacher->birthdate;


    if(SQLITE_OK != sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, count);
    sqlite3_bind_text(stmt, 2, name, strlen(name), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, surname, strlen(surname), SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, teacher->rating);
    sqlite3_bind_int(stmt, 5, teacher->subjects);
    sqlite3_bind_int(stmt, 6, teacher->years);
    sqlite3_bind_text(stmt, 7, birthdate, strlen(birthdate), SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        printf("Not inserted! %i\n", rc);
    }

    newStudentId = (int) sqlite3_last_insert_rowid (self->db);
    printf("Last inserted row: %i\n", newStudentId);
    if(rc!=SQLITE_DONE) return -1;
    sqlite3_reset(stmt);
    return newStudentId;
}

teacher_t db_getTeacherById(db_t * self, int id) {
    teacher_t t = teacher_new();
    const char * sqlScript = "select name,surname,rating,subjects,years,birthdate "
    "from Teacher where id = ?";
    static sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db, sqlScript, strlen(sqlScript) + 1, &stmt, 0)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, id);
    if(sqlite3_step(stmt)!=SQLITE_ROW) return NULL;

    teacher_setId(t, id);
    teacher_setName(t, (char *)sqlite3_column_text(stmt, 0));
    teacher_setSurname(t, (char *)sqlite3_column_text(stmt, 1));
    teacher_setRating(t, sqlite3_column_double(stmt, 2));
    teacher_setSubjects(t, sqlite3_column_int(stmt, 3));
    teacher_setYears(t, sqlite3_column_int(stmt, 4));
    teacher_setBirthdate(t, (char *)sqlite3_column_text(stmt, 5));
    sqlite3_reset(stmt);

    return t;
}

void teacher_update (db_t * self, teacher_t teacher) {
    static sqlite3_stmt * stmt = NULL;
    const char* sqlScript = "UPDATE Teacher SET name = ?, surname = ?, rating = ?, subjects = ?, years = ?, birthdate = ?, where id = ?";
    const char* name = teacher->name;
    const char* surname = teacher->surname;
    const char* birthdate = teacher->birthdate;
    int id = teacher->id;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db, sqlScript, strlen(sqlScript) + 1, &stmt, NULL)) {
        printf("Not prepared!\n : %i", sqlite3_prepare_v2(self->db, sqlScript, strlen(sqlScript) + 1, &stmt, NULL));
        puts(sqlite3_errmsg(stmt));
    }
    sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, surname, strlen(surname), SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, teacher->rating);
    sqlite3_bind_int(stmt, 4, teacher->subjects);
    sqlite3_bind_int(stmt, 5, teacher->years);
    sqlite3_bind_text(stmt, 6, birthdate, strlen(birthdate), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, id);

    sqlite3_step(stmt);
    sqlite3_reset(stmt);
}

void teacher_delete (db_t * self, teacher_t teacher) {
    const char * sqlScript = "delete FROM Teacher WHERE id = ?;";
    static sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db, sqlScript, strlen(sqlScript) + 1, &stmt, 0)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, teacher->id);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
}



