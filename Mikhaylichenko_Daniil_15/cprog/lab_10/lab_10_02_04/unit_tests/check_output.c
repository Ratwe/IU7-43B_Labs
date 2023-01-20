#include "../inc/unit_tests.h"

/*
 * NOTE: POSITIVE print_mults() TESTS
 */
START_TEST(test_print_mults_121)
{
    node_t *num_mults = NULL;
    convert_to_multipliers(&num_mults, 121);

    int rc = print_mults(&num_mults);

    free_list(&num_mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
}
END_TEST

START_TEST(test_print_mults_1)
{
    node_t *num_mults = NULL;
    convert_to_multipliers(&num_mults, 1);

    int rc = print_mults(&num_mults);

    free_list(&num_mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
}
END_TEST

/*
 * NOTE: NEGATIVE print_mults() TESTS
 */
START_TEST(test_print_mults_empty_list)
{
    node_t *num_mults = NULL;

    int rc = print_mults(&num_mults);
    ck_assert_int_eq(rc, EMPTY_LIST);
}
END_TEST

Suite *get_output_suite(void)
{
    Suite *suite = suite_create("output");

    TCase *tc_pos = tcase_create("Positive");
    tcase_add_test(tc_pos, test_print_mults_121);
    tcase_add_test(tc_pos, test_print_mults_1);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negative");
    tcase_add_test(tc_neg, test_print_mults_empty_list);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
