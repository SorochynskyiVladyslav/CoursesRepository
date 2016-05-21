#include "stock.h"
#include "list.h"

struct good_s {
    char name[MAX_NAME];
    int volume;
};

good_t good_new (char * nam, int vol) {
    good_t self = malloc (sizeof(struct good_s));
    strcpy(self->name, nam);
    self->volume = vol;
    return self;
}

char* good_getName (good_t self) {
    char* res = self->name[0];
    return res;
}

int good_getVolume (good_t self) {
    return self->volume;
}

void good_free (good_t self) {
    free(self);
}

struct record_s {
    good_t good;
    int time;
};

record_t record_new (good_t good) {
    record_t self = malloc(sizeof(struct record_s));
    self->good = good;
    self->time = rand() % 24;
}

int record_getTime (record_t rec) {
    return rec->time;
}

void record_free (record_t self) {
    free(self);
}

struct recordBook_s {
    record_t records[MAX_RECORDS];
    int size;
};

recordBook_t recordBook_new () {
    recordBook_t self = malloc (sizeof(struct recordBook_s));
    self->size = 0;
    return self;
}

void recordBook_free (recordBook_t self) {
    free(self);
}

void recordBook_add (recordBook_t self, record_t rec) {
    self->records[self->size] = rec;
    self->size++;
}

recordBook_t recordBook_getLastRecords (recordBook_t self, int N) {
    if (N > self->size || N < 0)
        N = self->size;
    recordBook_t res = recordBook_new();
    for (int i = N - 1; i >= 0 ; i--) {
        recordBook_add(res, self->records[i]);
    }
    return res;
}

struct stock_s {
    char name[MAX_NAME];
    recordBook_t history;
    int freespace;
    subList_t subs;
    int space;
    list_t goods;
};

stock_t stock_new (char* nam, int spac) {
    stock_t self = malloc (sizeof(struct stock_s));
    self->history = recordBook_new();
    self->goods = list_new();
    self->space = spac;
    self->subs = subList_new();
    self->freespace = spac;
    strcpy(self->name, nam);
    return self;
}

recordBook_t stock_getHistory (stock_t self) {
    return self->history;
}


good_t stock_remove (stock_t stock, good_t good) {
    good_t removed;
    int index = 0;
    for (int i = 0; i < list_size(stock->goods); i++) {
        if (good_getName(list_getGood(stock->goods, i)) == good_getName(good) && good_getVolume(list_getGood(stock->goods, i)) == good_getVolume(good)) {
            index = i;
            removed = list_getGood(stock->goods, i);
            break;
        }
    }
    list_del(stock->goods, index);
    stock->freespace += good_getVolume(removed);
    return removed;
}

int stock_getSpace (stock_t self) {
    return self->space;
}

int stock_getReservedSpacePercent (stock_t self) {
    float temp = (float) (self->space - self->freespace)/self->space;
    int res = (int) temp*100;
    return res;
}

list_t stock_getAllGoods (stock_t self) {
    return self->goods;
}

list_t stock_getVolumeGoods (stock_t self, int N) {
    list_t res = list_new();
    for (int i = 0; i < list_size(self->goods); i++) {
        if (good_getVolume(list_getGood(self->goods, i)) > N) {
            list_add(res, list_getGood(self->goods, i), list_size(res));
        }
    }
    return res;
}

void stock_free (stock_t self) {
    list_free(self->goods);
    recordBook_free(self->history);
    free(self);
}

char* stock_getName (stock_t self) {
    char* res = self->name[0];
    return res;
}

struct user_s {
    char name[MAX_NAME];
};

user_t user_new (const char* name) {
    user_t self = malloc(sizeof(struct user_s));
    strcpy(self->name, name);
    return self;
}

void user_free (user_t self) {
    free(self);
}

char* user_getName (user_t self) {
    char* name = self->name;
    return name;
}

struct sub_s {
    user_t user;
    Callback cb;
};

sub_t sub_new (user_t us, Callback Cb) {
    sub_t self = malloc (sizeof(struct sub_s));
    self->user = us;
    self->cb = Cb;
    return self;
}

void sub_free (sub_t sub) {
    free(sub);
}

struct subList_s {
    sub_t sub[MAX_SUBS];
    int count;
};

subList_t subList_new () {
    subList_t self = malloc(sizeof(struct subList_s));
    self->count = 0;
    return self;
}

int subList_getCount(subList_t subs) {
    return subs->count;
}

void stock_subscride (stock_t stock, user_t user, Callback cb) {
    sub_t sub = sub_new(user, cb);
    stock->subs->sub[stock->subs->count] = sub;
    stock->subs->count++;
}

void stock_add (stock_t stock, good_t good) {
    if (stock->space - good_getVolume(good) >= 0)
        list_add(stock->goods, good, list_size(stock->goods));
    else
        return;
    if (good_getVolume(good) > 10) {
        for (int i = 0; i < subList_getCount(stock->subs); i++){
            stock->subs->sub[i]->cb(good);
        }
    }
    stock->freespace -= good_getVolume(good);
    record_t rec = record_new(good);
    recordBook_add(stock->history, rec);
}
