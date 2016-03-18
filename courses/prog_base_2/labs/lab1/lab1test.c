#include "lab1head.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void new_void_zeroCount(void **state)
{
    postsystem_t p = postsystem_new();
    assert_int_equal(postsystem_getsize(p), 0);
    assert_int_equal(postsystem_getstatus(p), SYSTEM_EMPTY);
    postsystem_destroy(p);
}

static void add_oneValue_countOne(void **state)
{
    postsystem_t p = postsystem_new();
    postsystem_add(p, 100, 6523, "AABY");
    assert_int_equal(postsystem_getsize(p), 1);
    postsystem_destroy(p);
}

static void add_twoValues_countTwo(void **state)
{
    postsystem_t p = postsystem_new();
    postsystem_add(p, 100, 6523, "AABY");
    postsystem_add(p, 150, 8413, "AOBI");
    assert_int_equal(postsystem_getsize(p), 2);
    postsystem_destroy(p);
}

static void add_wrongValue_returnSpeedMistake(void **state)
{
    postsystem_t p = postsystem_new();
    assert_int_equal(postsystem_add(p, -170, 6523, "AABY"), RECORD_WRONGSPEED);
    postsystem_destroy(p);
}

static void add_wrongValue_returnNumberMistake(void **state)
{
    postsystem_t p = postsystem_new();
    assert_int_equal(postsystem_add(p, 170, 65423423, "AABY"), RECORD_WRONGNUMBER);
    postsystem_destroy(p);
}

static void add_wrongValue_returnSerialMistake(void **state)
{
    postsystem_t p = postsystem_new();
    assert_int_equal(postsystem_add(p, 170, 6523, "AABGFDY"), RECORD_WRONGSERIAL);
    postsystem_destroy(p);
}

static void remove_element_CountSize(void **state)
{
    postsystem_t p = postsystem_new();
    postsystem_add(p, 100, 6523, "AABY");
    postsystem_add(p, 150, 8413, "AOBI");
    postsystem_remove(p, 0);
    assert_int_equal(postsystem_getsize(p), 1);
    postsystem_destroy(p);
}

int testSystem (void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_oneValue_countOne),
        cmocka_unit_test(add_twoValues_countTwo),
        cmocka_unit_test(add_wrongValue_returnSpeedMistake),
        cmocka_unit_test(add_wrongValue_returnNumberMistake),
        cmocka_unit_test(add_wrongValue_returnSerialMistake),
        cmocka_unit_test(remove_element_CountSize),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
