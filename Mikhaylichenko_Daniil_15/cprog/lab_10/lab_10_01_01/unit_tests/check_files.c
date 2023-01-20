#include "../inc/unit_tests.h"

/*
 * NOTE: POSITIVE file_open() TESTS
 */
START_TEST(test_file_open_correct)
{
    FILE *file = NULL;

    int rc = file_open((const FILE **const)&file, "./out/test.txt", WRITE_MODE);
    file_close(&file);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
}
END_TEST

/*
 * NOTE: NEGATIVE file_open() TESTS
 */
START_TEST(test_file_open_wrong)
{
    FILE *file = NULL;

    int rc = file_open((const FILE **const)&file, "wrong_file.txt", READ_MODE);
    ck_assert_int_eq(rc, FILE_OPEN_ERROR);
}
END_TEST

/*
 * NOTE: POSITIVE file_close() TESTS
 */
START_TEST(test_file_close_correct)
{
    FILE *file = NULL;
    file_open((const FILE **const)&file, "./unit_tests/data/one_element.txt", READ_MODE);

    int rc = file_close(&file);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
}
END_TEST

Suite *get_files_suite(void)
{
    Suite *suite = suite_create("files");

    TCase *tc_pos = tcase_create("Positives");
    tcase_add_test(tc_pos, test_file_open_correct);
    tcase_add_test(tc_pos, test_file_close_correct);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negatives");
    tcase_add_test(tc_neg, test_file_open_wrong);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
