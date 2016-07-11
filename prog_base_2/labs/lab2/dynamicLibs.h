#ifndef DYNAMICLIBS_H_INCLUDED
#define DYNAMICLIBS_H_INCLUDED

#include "queue.h"
#include <windows.h>

typedef int (*chk_f)(queue_t q);
typedef void (*react_f)(void);

typedef struct dynamic_s {
    HANDLE hLib;
    chk_f chk;
    react_f react;
} dynamic_t;

#endif // DYNAMICLIBS_H_INCLUDED
