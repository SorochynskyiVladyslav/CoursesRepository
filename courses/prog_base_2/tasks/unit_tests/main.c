#include <stdio.h>
#include <stdlib.h>
#include "modules.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

static void new_void_zeroCount(void **state)
{
    list_t p = list_new();
    assert_int_equal(list_getsize(p), 0);
    list_destroy(p);
}

static void add_oneValue_countOne(void **state)
{
    list_t p = list_new();
    p = list_add(p, 5, 6, "Kyiv", 0);
    assert_int_equal(list_getsize(p), 1);
    list_destroy(p);
}

static void add_twoValues_countTwo(void **state)
{
    list_t p = list_new();
    p = list_add(p, 5, 6, "Kyiv", 0);
    p = list_add(p, 8, 2, "Lviv", 1);
    assert_int_equal(list_getsize(p), 2);
    list_destroy(p);
}

static void remove_element_CountSize(void **state)
{
    list_t p = list_new();
    p = list_add(p, 5, 6, "Kyiv", 0);
    p = list_add(p, 8, 2, "Lviv", 1);
    p = list_remove(p, 1);
    assert_int_equal(list_getsize(p), 1);
    list_destroy(p);
}

static void count_distance_Correct(void **state)
{
    list_t p = list_new();
    double distance = 0;
    p = list_add(p, 5, 6, "Kyiv", 0);
    p = list_add(p, 8, 2, "Lviv", 1);
    distance = (double) sqrt(pow(5 - 8, 2) + pow(6 - 2, 2));
    assert_int_equal(list_distance(p, 0, 1), distance);
    list_destroy(p);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_oneValue_countOne),
        cmocka_unit_test(add_twoValues_countTwo),
        cmocka_unit_test(remove_element_CountSize),
        cmocka_unit_test(count_distance_Correct),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
