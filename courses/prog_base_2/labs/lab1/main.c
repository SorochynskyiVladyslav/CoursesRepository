#include <stdio.h>
#include <stdlib.h>
#include "lab1head.h"

int main()
{
    testSystem();
    puts(" ");
    postsystem_t p = postsystem_new();
    system_status status = postsystem_getstatus(p);
    postsystem_add(p, 139, 1423, "OABY");
    postsystem_add(p, 120, 6579, "HYBY");
    postsystem_add(p, 97, 2393, "OABY");
    postsystem_add(p, 101, 6523, "OABY");
    postsystem_add(p, 137, 1163, "DAKY");
    postsystem_add(p, 95, 1446, "KABY");
    postsystem_add(p, 167, 7427, "OABY");
    postsystem_add(p, 118, 6523, "AABY");
    status = postsystem_getstatus(p);
    postsystem_print(p);


    postsystem_destroy(p);
    return 0;
}
