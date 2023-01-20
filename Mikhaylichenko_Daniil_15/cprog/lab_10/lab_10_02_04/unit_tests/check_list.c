#include "../inc/unit_tests.h"

/*
 * NOTE: POISITVE convert_to_multipliers() TESTS
 */
START_TEST(test_convert_to_multipliers_121)
{
    int rc;

    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 11;
    right_mults->power = 2;
    right_mults->next = NULL;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 121);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&mults);
    free_list(&right_mults);
}
END_TEST

START_TEST(test_convert_to_multipliers_112)
{
    int rc;

    node_t *right_mults_head = malloc(sizeof(node_t));
    node_t *right_mults_node = malloc(sizeof(node_t));
    right_mults_head->num = 2;
    right_mults_head->power = 4;
    right_mults_node->num = 7;
    right_mults_node->power = 1;
    right_mults_head->next = right_mults_node;
    right_mults_node->next = NULL;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 112);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults_head, &mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&mults);
    free_list(&right_mults_head);
}
END_TEST

START_TEST(test_convert_to_multipliers_1)
{
    int rc;

    node_t *right_mults = malloc(sizeof(node_t));
    right_mults->num = 1;
    right_mults->power = 1;
    right_mults->next = NULL;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 1);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&right_mults, &mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&mults);
    free_list(&right_mults);
}
END_TEST

/*
 * NOTE: NEGATIVE convert_to_multipliers() TESTS
 */
START_TEST(test_convert_to_multipliers_0)
{
    int rc;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 0);
    ck_assert_int_eq(rc, WRONG_INPUT);
}
END_TEST

/*
 * NOTE: POISITVE convert_to_num() TESTS
 */
START_TEST(test_convert_to_num_to_121)
{
    int rc;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 121);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    int num;
    rc = convert_to_num(&mults, &num);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(num, 121);

    free_list(&mults);
}

START_TEST(test_convert_to_num_to_112)
{
    int rc;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 112);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    int num;
    rc = convert_to_num(&mults, &num);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(num, 112);

    free_list(&mults);
}
END_TEST


START_TEST(test_convert_to_num_to_1)
{
    int rc;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 1);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    int num;
    rc = convert_to_num(&mults, &num);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(num, 1);

    free_list(&mults);
}

/*
 * NOTE: NEGATIVE convert_to_num() TESTS
 */
START_TEST(test_convert_to_num_empty_list)
{
    int rc;

    node_t *mults = NULL;

    int num;
    rc = convert_to_num(&mults, &num);
    ck_assert_int_eq(rc, EMPTY_LIST);
}
END_TEST

/*
 * NOTE: POISITVE reverse() TESTS
 */
START_TEST(test_reverse_112_mults)
{
    int rc;

    node_t *right_mults_head = malloc(sizeof(node_t));
    node_t *right_mults_node = malloc(sizeof(node_t));
    right_mults_head->num = 7;
    right_mults_head->power = 1;
    right_mults_node->num = 2;
    right_mults_node->power = 4;
    right_mults_head->next = right_mults_node;
    right_mults_node->next = NULL;

    node_t *mults = NULL;
    rc = convert_to_multipliers(&mults, 112);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    node_t *reversed_mults = reverse(mults);

    rc = compare_lists(&right_mults_head, &reversed_mults);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&reversed_mults);
    free_list(&right_mults_head);
}
END_TEST


/*
 * NOTE: NEGATIVE reverse() TESTS
 */
START_TEST(test_reverse_empty_list)
{
    node_t *mults = NULL;
    node_t *reversed_mults = reverse(mults);
    ck_assert_ptr_null(reversed_mults);
}
END_TEST

Suite *get_list_suite(void)
{
    Suite *suite = suite_create("list");

    TCase *tc_pos = tcase_create("Positive");
    tcase_add_test(tc_pos, test_convert_to_multipliers_121);
    tcase_add_test(tc_pos, test_convert_to_multipliers_112);
    tcase_add_test(tc_pos, test_convert_to_multipliers_1);
    tcase_add_test(tc_pos, test_convert_to_num_to_121);
    tcase_add_test(tc_pos, test_convert_to_num_to_112);
    tcase_add_test(tc_pos, test_convert_to_num_to_1);
    tcase_add_test(tc_pos, test_reverse_112_mults);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negative");
    tcase_add_test(tc_neg, test_convert_to_multipliers_0);
    tcase_add_test(tc_neg, test_convert_to_num_empty_list);
    tcase_add_test(tc_neg, test_reverse_empty_list);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
