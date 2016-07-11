#include <stdio.h>
#include <stdlib.h>
#include "lab1head.h"

int main()
{
    testSystem();
    puts(" ");
    postsystem_t p = postsystem_new();
    post_t po1 = post_new(139, 1423, "OABY");
    post_t po2 = post_new(120, 6579, "HYBY");
    post_t po3 = post_new(97, 2393, "OABY");
    post_t po4 = post_new(101, 6523, "OABY");
    post_t po5 = post_new(137, 1163, "DAKY");
    post_t po6 = post_new(95, 1446, "KABY");
    post_t po7 = post_new(167, 7427, "OABY");
    post_t po8 = post_new(118, 6523, "AABY");

    system_status status = postsystem_getstatus(p);
    postsystem_add(p, po1);
    postsystem_add(p, po2);
    postsystem_add(p, po3);
    postsystem_add(p, po4);
    postsystem_add(p, po5);
    postsystem_add(p, po6);
    postsystem_add(p, po7);
    postsystem_add(p, po8);
    status = postsystem_getstatus(p);
    postsystem_print(p);


    postsystem_destroy(p);
    return 0;
}
