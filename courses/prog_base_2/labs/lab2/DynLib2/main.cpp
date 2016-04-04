#include "main.h"
#include <stdio.h>

// a sample exported function
int DLL_EXPORT Check (queue_t q)
{
    int i, status = 0;
    for (i = 0; queue_getsize(q) != 0; i++){
        if (queue_remove(q) < 3) {
            status++;
        }
        //if (status >= 2)
        //    break;
    }
    if (status >= 2)
        return 1;
    else return 0;
}

void DLL_EXPORT Reaction (void) {
    printf("Fired!\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
