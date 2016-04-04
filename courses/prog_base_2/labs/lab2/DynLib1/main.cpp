#include "main.h"
#include <stdio.h>

// a sample exported function
int DLL_EXPORT Check(queue_t q)
{
    int sum = 0, i;
    for (i = 0; queue_getsize(q) != 0; i++){
        sum += queue_remove(q);
    }
    if (sum < 40)
        return 1;
    else return 0;
}

void DLL_EXPORT Reaction (void) {
    printf("Warning\n");
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
