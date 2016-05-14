#ifndef SUPADRIVE_H_INCLUDED
#define SUPADRIVE_H_INCLUDED

#define MAX_FILES 50
#define MAX_BYTES 1000

#include "file.h"
#include <time.h>

typedef struct SupaDrive_s * SupaDrive_t;
typedef void (*Callback) (user_t user, file_t file, SupaDrive_t drive);

SupaDrive_t SupaDrive_new ();
void SupaDrive_free (SupaDrive_t self);
int SupaDrive_getBytes (SupaDrive_t self);
void SupaDrive_add (file_t file, SupaDrive_t drive, Callback cb[2], user_t users[]);
file_t SupaDrive_delete (SupaDrive_t drive, file_t file);
void SuccessMessage (user_t user, file_t file, SupaDrive_t drive);
void FailureMessage(user_t user, file_t file, SupaDrive_t drive);

#endif // SUPADRIVE_H_INCLUDED
