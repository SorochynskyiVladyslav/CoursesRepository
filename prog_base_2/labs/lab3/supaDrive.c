#include "supaDrive.h"

struct SupaDrive_s {
    file_t files[MAX_FILES];
    subList_t subs;
    int amount;
    int bytes;
};

SupaDrive_t SupaDrive_new () {
    SupaDrive_t self = malloc(sizeof(struct SupaDrive_s));
    self->subs = subList_new();
    self->amount = 0;
    self->bytes = 0;
    return self;
}

void SupaDrive_free (SupaDrive_t self) {
    subList_free(self->subs);
    free(self);
}

int SupaDrive_getBytes (SupaDrive_t self) {
    return self->bytes;
}

struct sub_s {
    user_t user;
    Callback cb[2];
};

sub_t sub_new (user_t us, Callback CB1, Callback CB2) {
    sub_t self = malloc (sizeof(struct sub_s));
    self->user = us;
    self->cb[0] = CB1;
    self->cb[1] = CB2;
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

void SupaDrive_subscride (SupaDrive_t drive, user_t user, Callback cb1, Callback cb2) {
    sub_t sub = sub_new(user, cb1, cb2);
    drive->subs->sub[drive->subs->count] = sub;
    drive->subs->count++;
}

void subList_unsubscride (subList_t subs, user_t user) {
    if (subs->count == 0)
        return;
    int i = 0;
    for (i = 0; i < subs->count; i++) {
        if (subs->sub[i]->user == user)
            break;
    }
    for (int j = i; i < subs->count; j++) {
        subs->sub[j] = subs->sub[j+1];
    }
    subs->count--;
}

void subList_free(subList_t self) {
    for (int i = 0; i < self->count; i++) {
        sub_free(self->sub[i]);
    }
    free(self);
}



void SupaDrive_add (SupaDrive_t drive, file_t file) {
    if (file_getBytes(file) + SupaDrive_getBytes(drive) <= MAX_BYTES){
        drive->files[drive->amount] = file;
        drive->amount++;
        drive->bytes += file_getBytes(file);
        for (int i = 0; i < subList_getCount(drive->subs); i++) {
            if (drive->subs->sub[i]->user != file_getUser(file)) {
                drive->subs->sub[i]->cb[0](drive->subs->sub[i]->user, file, drive);
            }
        }
    }
    else
        for (int i = 0; i < subList_getCount(drive->subs); i++) {
            if (drive->subs->sub[i]->user != file_getUser(file)) {
                drive->subs->sub[i]->cb[1](drive->subs->sub[i]->user, file, drive);
            }
        }
}

file_t SupaDrive_delete (SupaDrive_t drive, file_t file) {
    int index = 0;
    for (int i = 0; i < drive->amount; i++) {
        if (drive->files[i] == file) {
            index = i;
            i = drive->amount;
        }
    }
    file_t deleted = drive->files[index];
    for (int i = 0; i < drive->amount - index; i++) {
        drive->files[index + i] = drive->files[index + i + 1];
    }
    drive->amount--;
    drive->bytes -= file_getBytes(deleted);
    return deleted;
}

void SuccessMessage (user_t user, file_t file, SupaDrive_t drive) {
    char* us = user_getName(user);
    char* author = file_getAuthor(file);
    char* fileName = file_getName(file);
    int fileBytes = file_getBytes(file);
    int driveBytes = SupaDrive_getBytes(drive);
    int freeSpace = MAX_BYTES - driveBytes;
    printf(" %s got notification that %s added file '%s' (%i bytes)\n Remaining space on SupaDrive %i bytes \n\n",
           us, author, fileName, fileBytes, freeSpace);
}

void FailureMessage(user_t user, file_t file, SupaDrive_t drive) {
    char* us = user_getName(user);
    char* author = file_getAuthor(file);
    char* fileName = file_getName(file);
    int fileBytes = file_getBytes(file);
    int driveBytes = SupaDrive_getBytes(drive);
    int requiredSpace =  driveBytes + fileBytes - MAX_BYTES;
    printf(" %s got notification that %s failed to add file '%s' (%i bytes)\n Need %i additional bytes on SupaDrive\n\n",
           us, author, fileName, fileBytes, requiredSpace);
}

int subList_getCount (subList_t subs) {
    return subs->count;
}
