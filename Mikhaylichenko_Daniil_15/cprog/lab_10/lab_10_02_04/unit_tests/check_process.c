#include "../inc/unit_tests.h"

/*
 * NOTE: POSITIVE mult_lists() TESTS
 */
START_TEST(test_mult_lists_1_1)
{
    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 1;
    right_mults->power = 1;
    right_mults->next = NULL;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 1);
    convert_to_multipliers(&second, 1);

    int rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&first);
    free_list(&second);
    free_list(&res);
    free_list(&right_mults);
}
END_TEST

START_TEST(test_mult_lists_8_14)
{
    node_t *right_mults_head = malloc(sizeof(node_t));
    node_t *right_mults_node = malloc(sizeof(node_t));
    right_mults_head->num = 2;
    right_mults_head->power = 4;
    right_mults_node->num = 7;
    right_mults_node->power = 1;
    right_mults_head->next = right_mults_node;
    right_mults_node->next = NULL;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 8);
    convert_to_multipliers(&second, 14);

    int rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults_head, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&first);
    free_list(&second);
    free_list(&res);
    free_list(&right_mults_head);
}
END_TEST

START_TEST(test_mult_lists_121_121)
{
    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 11;
    right_mults->power = 4;
    right_mults->next = NULL;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 121);
    convert_to_multipliers(&second, 121);

    int rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&first);
    free_list(&second);
    free_list(&res);
    free_list(&right_mults);
}
END_TEST

/*
 * NOTE: NEGATIVE mult_lists() TESTS
 */
START_TEST(test_mult_lists_first_is_empty)
{
    int rc;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&second, 121);

    rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EMPTY_LIST);

    free_list(&second);
}
END_TEST

START_TEST(test_mult_lists_second_is_empty)
{
    int rc;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 121);

    rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EMPTY_LIST);

    free_list(&first);
}
END_TEST

/*
 * NOTE: POSITIVE sqr_list() TESTS
 */
START_TEST(test_sqr_list_121)
{
    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 11;
    right_mults->power = 4;
    right_mults->next = NULL;

    node_t *mults = NULL;
    convert_to_multipliers(&mults, 121);

    int rc = sqr_list(&mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&right_mults);
    free_list(&mults);
}


START_TEST(test_sqr_list_112)
{
    node_t *right_mults_head = malloc(sizeof(node_t));
    node_t *right_mults_node = malloc(sizeof(node_t));
    right_mults_head->num = 2;
    right_mults_head->power = 8;
    right_mults_node->num = 7;
    right_mults_node->power = 2;
    right_mults_head->next = right_mults_node;
    right_mults_node->next = NULL;

    node_t *mults = NULL;
    convert_to_multipliers(&mults, 112);

    int rc = sqr_list(&mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults_head, &mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&right_mults_head);
    free_list(&mults);
}

/*
 * NOTE: NEGATIVE sqr_list() TESTS
 */
START_TEST(test_sqr_list_empty)
{
    int rc;

    node_t *mults = NULL;

    rc = sqr_list(&mults);
    ck_assert_int_eq(rc, EMPTY_LIST);
}
END_TEST

/*
 * NOTE: POSITIVE divide_lists() TESTS
 */
START_TEST(test_divide_lists_1_1)
{
    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 1;
    right_mults->power = 1;
    right_mults->next = NULL;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 1);
    convert_to_multipliers(&second, 1);

    int rc = divide_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&first);
    free_list(&second);
    free_list(&res);
    free_list(&right_mults);
}
END_TEST

START_TEST(test_divide_lists_12_3)
{
    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 2;
    right_mults->power = 2;
    right_mults->next = NULL;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 12);
    convert_to_multipliers(&second, 3);

    int rc = divide_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &res);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&first);
    free_list(&second);
    free_list(&res);
    free_list(&right_mults);
}
END_TEST

/*
 * NOTE: NEGATIVE devide_lists() TESTS
 */
START_TEST(test_divide_lists_first_is_empty)
{
    int rc;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&second, 121);

    rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EMPTY_LIST);

    free_list(&second);
}
END_TEST

START_TEST(test_divide_lists_second_is_empty)
{
    int rc;

    node_t *first = NULL, *second = NULL, *res = NULL;
    convert_to_multipliers(&first, 121);

    rc = mult_lists(&first, &second, &res);
    ck_assert_int_eq(rc, EMPTY_LIST);

    free_list(&first);
}
END_TEST

START_TEST(test_divide_lists_0)
{
    int rc;

    node_t *first = malloc(sizeof(node_t));
    node_t *second = NULL;
    node_t *res = NULL;

    first->num = 0;
    first->power = 0;
    first->next = NULL;
    convert_to_multipliers(&second, 121);

    rc = divide_lists(&first, &second, &res);
    ck_assert_int_eq(rc, WRONG_INPUT);

    free_list(&first);
    free_list(&second);
}
END_TEST

Suite *get_process_suite(void)
{
    Suite *suite = suite_create("process");

    TCase *tc_pos = tcase_create("Positive");
    tcase_add_test(tc_pos, test_mult_lists_1_1);
    tcase_add_test(tc_pos, test_mult_lists_8_14);
    tcase_add_test(tc_pos, test_mult_lists_121_121);
    tcase_add_test(tc_pos, test_sqr_list_121);
    tcase_add_test(tc_pos, test_sqr_list_112);
    tcase_add_test(tc_pos, test_divide_lists_1_1);
    tcase_add_test(tc_pos, test_divide_lists_12_3);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negative");
    tcase_add_test(tc_neg, test_mult_lists_first_is_empty);
    tcase_add_test(tc_neg, test_mult_lists_second_is_empty);
    tcase_add_test(tc_neg, test_sqr_list_empty);
    tcase_add_test(tc_neg, test_divide_lists_first_is_empty);
    tcase_add_test(tc_neg, test_divide_lists_second_is_empty);
    tcase_add_test(tc_neg, test_divide_lists_0);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
