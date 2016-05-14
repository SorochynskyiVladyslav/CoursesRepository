#include "supaDrive.h"
#include "test.h"
#include <windows.h>

int main()
{
    //test_SupaDrive();
    puts("");
    srand(time(NULL));
    user_t users[4];
    Callback cb1 = &SuccessMessage;
    Callback cb2 = &FailureMessage;
    users[0] = user_new("Vlad");
    users[1] = user_new("Ruslan");
    users[2] = user_new("Elena");
    users[3] = user_new("Viktor");

    subList_t subscriders = subList_new();
    for (int i = 0; i < 4; i++) {
        subList_subscride(subscriders, users[i], cb1, cb2);
    }

    file_t files[9];
    files[0] = file_new ("File1", users[rand()%4], rand()%101+100);
    files[1] = file_new ("File2", users[rand()%4], rand()%101+100);
    files[2] = file_new ("File3", users[rand()%4], rand()%101+100);
    files[3] = file_new ("File4", users[rand()%4], rand()%101+100);
    files[4] = file_new ("File5", users[rand()%4], rand()%101+100);
    files[5] = file_new ("File6", users[rand()%4], rand()%101+100);
    files[6] = file_new ("File7", users[rand()%4], rand()%101+100);
    files[7] = file_new ("File8", users[rand()%4], rand()%101+100);
    files[8] = file_new ("File9", users[rand()%4], rand()%101+100);
    SupaDrive_t drive = SupaDrive_new();

    for (int i = 0; i < 9; i++){
        Sleep(1000);
        SupaDrive_add(drive, subscriders, files[i]);
    }

    SupaDrive_free(drive);
    subList_free(subscriders);

    for(int i = 0; i < 9; i++) {
        file_free(files[i]);
    }
    for (int i = 0; i < 4; i++) {
        user_free(users[i]);
    }
    return 0;
}
