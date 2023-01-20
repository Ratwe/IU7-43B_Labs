#include "../inc/unit_tests.h"

/*
 * NOTE: POSITIVE comparator() TESTS
 */
START_TEST(test_comparator_first_one_is_bigger)
{
    int num1 = 100, num2 = 1;
    void *pnum1 = &num1, *pnum2 = &num2;
    int compare = comparator(pnum1, pnum2);
    ck_assert_int_eq(1, compare > 0);
}
END_TEST

START_TEST(test_comparator_equal)
{
    int num1 = 100, num2 = 100;
    void *pnum1 = &num1, *pnum2 = &num2;
    int compare = comparator(pnum1, pnum2);
    ck_assert_int_eq(1, compare == 0);
}
END_TEST

START_TEST(test_comparator_second_one_is_bigger)
{
    int num1 = 1, num2 = 100;
    void *pnum1 = &num1, *pnum2 = &num2;
    int compare = comparator(pnum1, pnum2);
    ck_assert_int_eq(1, compare < 0);
}
END_TEST

Suite *get_process_suite(void)
{
    Suite *suite = suite_create("process");

    TCase *tc_pos = tcase_create("Positives");
    tcase_add_test(tc_pos, test_comparator_first_one_is_bigger);
    tcase_add_test(tc_pos, test_comparator_equal);
    tcase_add_test(tc_pos, test_comparator_second_one_is_bigger);
    suite_add_tcase(suite, tc_pos);

    return suite;
}
