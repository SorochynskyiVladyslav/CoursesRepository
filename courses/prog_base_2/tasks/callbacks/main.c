#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef void (*Callback)(const char *, int);

void server (Callback cb1, Callback cb2);

void onClientConnectedCB (const char * name, int pos) { printf("Client on position %i connected:    %s\n", pos, name); }
void onClientDisconnected (const char * name, int pos) { printf("Client on position %i disconnected:    %s\n", pos, name); }

int main(void)
{
    srand(time(NULL));
    Callback cb1 = onClientConnectedCB;
    Callback cb2 = onClientDisconnected;
    server (cb1, cb2);
    return 0;
}

void server (Callback cb1, Callback cb2) {
    int i, j;
    char c[10][50];
    char* deleted;
    char* names[10];
    for (i = 0; i < 10; i++){
        names[i] = NULL;
    }
    while (j != 11) {
        i = rand() % 9;
        puts("Checking if position is vacant...");
        Sleep(1000);
        if (names[i] == NULL){
            printf("Enter client's name:    ");
            names[i] = gets(c[i]);
            cb1(names[i], i);
            Sleep(1000);
        }
        else {
            deleted = names[i];
            names[i] = NULL;
            cb2(deleted, i);
            Sleep(1000);
        }
        j++;
    }
    puts("Finished");
}
