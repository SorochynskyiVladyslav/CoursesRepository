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

void SupaDrive_add (file_t file, SupaDrive_t drive, Callback func1, Callback func2) {
    if (file_getBytes(file) + SupaDrive_getBytes(drive) <= MAX_BYTES){
        drive->files[drive->amount] = file;
        drive->amount++;
        drive->bytes += file_getBytes(file);
        func1(file, drive);
    }
    else
        func2(file, drive);
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

void SuccessMessage (file_t file, SupaDrive_t drive) {
    char* user = file_getAuthor(file);
    char* fileName = file_getName(file);
    int fileBytes = file_getBytes(file);
    int driveBytes = SupaDrive_getBytes(drive);
    int freeSpace = MAX_BYTES - driveBytes;
    printf("%s added file '%s'(%i bytes) succesfully\nRemaining space on SupaDrive: %i bytes\n\n",
           user, fileName, fileBytes, freeSpace);
}

void FailureMessage(file_t file, SupaDrive_t drive) {
    char* user = file_getAuthor(file);
    char* fileName = file_getName(file);
    int fileBytes = file_getBytes(file);
    int driveBytes = SupaDrive_getBytes(drive);
    int requiredSpace =  driveBytes + fileBytes - MAX_BYTES;
    printf("%s failed to add file '%s'(%i bytes) \nNot enough space on SupaDrive: additional %i bytes required\n\n",
           user, fileName, fileBytes, requiredSpace);
}
