#include "supaDrive.h"

struct SupaDrive_s {
    file_t files[MAX_FILES];
    int amount;
    int bytes;
};

SupaDrive_t SupaDrive_new () {
    SupaDrive_t self = malloc(sizeof(struct SupaDrive_s));
    self->amount = 0;
    self->bytes = 0;
    return self;
}

void SupaDrive_free (SupaDrive_t self) {
    free(self);
}

int SupaDrive_getBytes (SupaDrive_t self) {
    return self->bytes;
}

void SupaDrive_add (file_t file, SupaDrive_t drive, Callback cb[2], user_t users[]) {
    if (file_getBytes(file) + SupaDrive_getBytes(drive) <= MAX_BYTES){
        drive->files[drive->amount] = file;
        drive->amount++;
        drive->bytes += file_getBytes(file);
        for (int i = 0; i < sizeof(users); i++) {
            if (users[i] != file_getUser(file)) {
                cb[0](users[i], file, drive);
            }
        }
    }
    else
        for (int i = 0; i < sizeof(users); i++) {
            if (users[i] != file_getUser(file)) {
                cb[1](users[i], file, drive);
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
