#ifndef SUPADRIVE_H_INCLUDED
#define SUPADRIVE_H_INCLUDED

#define MAX_FILES 50
#define MAX_BYTES 1000
#define MAX_SUBS 15

#include "file.h"
#include <time.h>

typedef struct SupaDrive_s * SupaDrive_t;
typedef void (*Callback) (user_t user, file_t file, SupaDrive_t drive);
typedef struct sub_s * sub_t;
typedef struct subList_s * subList_t;

SupaDrive_t SupaDrive_new ();
void SupaDrive_free (SupaDrive_t self);
int SupaDrive_getBytes (SupaDrive_t self);
void SupaDrive_add (SupaDrive_t drive, subList_t subs, file_t file);
file_t SupaDrive_delete (SupaDrive_t drive, file_t file);
void SuccessMessage (user_t user, file_t file, SupaDrive_t drive);
void FailureMessage(user_t user, file_t file, SupaDrive_t drive);

sub_t sub_new (user_t us, Callback CB1, Callback CB2);
subList_t subList_new ();
void subList_subscride (subList_t subs, user_t user, Callback cb1, Callback cb2);
void subList_unsubscride (subList_t subs, user_t user);
int subList_getCount (subList_t subs);


#endif // SUPADRIVE_H_INCLUDED
