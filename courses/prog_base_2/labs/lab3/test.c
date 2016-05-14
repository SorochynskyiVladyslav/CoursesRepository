#include "test.h"
#include "supaDrive.h"

void TestMessage (file_t file, SupaDrive_t drive) {
}

static void new_void_zeroCount(void **state)
{
    SupaDrive_t drive = SupaDrive_new();
    assert_int_equal(SupaDrive_getBytes(drive), 0);
    SupaDrive_free(drive);
}

static void add_OneFile_countBytes(void **state)
{
    SupaDrive_t drive = SupaDrive_new();
    user_t user[2];
    user[0] = user_new("testUser1");
    user[1] = user_new("testUser2");
    Callback cb[2];
    cb[0] = &TestMessage;
    cb[2] = &TestMessage;
    int fileBytes = 100;
    file_t file = file_new("test", user[0], fileBytes);
    SupaDrive_add(file, drive, cb, user);
    assert_int_equal(SupaDrive_getBytes(drive), fileBytes);
    SupaDrive_free(drive);
    file_free(file);
    user_free(user[0]);
    user_free(user[1]);
}

static void add_TwoFiles_countBytes(void **state)
{
    SupaDrive_t drive = SupaDrive_new();
    user_t user[2];
    user[0] = user_new("testUser1");
    user[1] = user_new("testUser2");
    Callback cb[2];
    cb[0] = &TestMessage;
    cb[2] = &TestMessage;
    int fileBytes1 = 100;
    int fileBytes2 = 150;
    file_t file1 = file_new("test1", user, fileBytes1);
    file_t file2 = file_new("test1", user, fileBytes2);
    int sumBytes = fileBytes1 + fileBytes2;
    SupaDrive_add(file1, drive, cb, user);
    SupaDrive_add(file2, drive, cb, user);
    assert_int_equal(SupaDrive_getBytes(drive), sumBytes);
    SupaDrive_free(drive);
    file_free(file1);
    file_free(file2);
    user_free(user[0]);
    user_free(user[1]);
}

static void remove_File_countBytes(void **state) {
    SupaDrive_t drive = SupaDrive_new();
    user_t user[2];
    user[0] = user_new("testUser1");
    user[1] = user_new("testUser2");
    file_t file = file_new("test1", user[0], 150);
    Callback cb[2];
    cb[0] = &TestMessage;
    cb[2] = &TestMessage;
    SupaDrive_add(file, drive, cb, user);
    SupaDrive_delete(drive, file);
    assert_int_equal(SupaDrive_getBytes(drive), 0);
    SupaDrive_free(drive);
    user_free(user[0]);
    user_free(user[1]);
}

int test_SupaDrive(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_OneFile_countBytes),
        cmocka_unit_test(add_TwoFiles_countBytes),
        cmocka_unit_test(remove_File_countBytes),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
