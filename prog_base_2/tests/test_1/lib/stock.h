#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#define MAX_NAME 50
#define MAX_RECORDS 50
#define MAX_NAME 100
#define MAX_SUBS 10

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct good_s * good_t;
good_t good_new (char * nam, int vol);
char* good_getName (good_t self);
int good_getVolume (good_t self);
void good_free (good_t self);


typedef struct stock_s * stock_t;
stock_t stock_new (char* nam, int spac);
void stock_free (stock_t self);
char* stock_getName (stock_t self);
void stock_add (stock_t stock, good_t good);
good_t stock_remove (stock_t stock, good_t good);


typedef struct record_s * record_t;
record_t record_new (good_t good);
int record_getTime (record_t rec);
void record_free (record_t self);


typedef struct recordBook_s * recordBook_t;
recordBook_t recordBook_new ();
void recordBook_free (recordBook_t self);
void recordBook_add (recordBook_t self, record_t rec);
recordBook_t recordBook_getLastRecords (recordBook_t self, int N);


typedef struct user_s * user_t;
user_t user_new (const char* name);
void user_free (user_t self);
char* user_getName (user_t self);


typedef struct sub_s * sub_t;
typedef struct subList_s * subList_t;

typedef void (*Callback) (good_t good);

sub_t sub_new (user_t us, Callback Cb);
subList_t subList_new ();
void stock_subscride (stock_t stock, user_t user, Callback cb);
recordBook_t stock_getHistory (stock_t self);
void subList_unsubscride (subList_t subs, user_t user);
int subList_getCount (subList_t subs);




#endif // STOCK_H_INCLUDED
