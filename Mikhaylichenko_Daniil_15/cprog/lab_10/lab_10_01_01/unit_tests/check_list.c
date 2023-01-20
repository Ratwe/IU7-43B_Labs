#include "../inc/unit_tests.h"

/*
 * NOTE: POSITIVE fill_list() TESTS
 */
START_TEST(test_fill_list_3)
{
    node_t *head = malloc(sizeof(node_t));
    node_t *node1 = malloc(sizeof(node_t));
    node_t *node2 = malloc(sizeof(node_t));
    int right_array[3] = { 2, 1, 3 };
    head->next = node1;
    node1->next = node2;
    node2->next = NULL;
    head->data = &right_array[0];
    node1->data = &right_array[1];
    node2->data = &right_array[2];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    int rc = fill_list("./unit_tests/data/three_elements.txt", &list, &arr);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&head, &list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&list);
    free_list(&head);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE fill_list() TESTS
 */
START_TEST(test_fill_list_one_element)
{
    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    int rc = fill_list("./unit_tests/data/one_element.txt", &list, &arr);
    ck_assert_int_eq(rc, WRONG_DATA);
}
END_TEST

/*
 * NOTE: POSITIVE pop_front() TESTS
 */
START_TEST(test_pop_front)
{
    node_t *node1 = malloc(sizeof(node_t));
    node_t *node2 = malloc(sizeof(node_t));
    int right_array[2] = { 1, 3 };
    node1->next = node2;
    node2->next = NULL;
    node1->data = &right_array[0];
    node2->data = &right_array[1];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    fill_list("./unit_tests/data/three_elements.txt", &list, &arr);
    void *data = pop_front(&list);
    int rc = compare_lists(&node1, &list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(*(int*)data, 2);

    free_list(&list);
    free_list(&node1);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE pop_front() TESTS
 */
START_TEST(test_pop_front_empty)
{
    node_t *list = NULL;
    node_t *new_list = pop_front(&list);
    ck_assert_ptr_null(new_list);
}
END_TEST

/*
 * NOTE: POSITIVE pop_back() TESTS
 */
START_TEST(test_pop_back)
{
    node_t *head = malloc(sizeof(node_t));
    node_t *node1 = malloc(sizeof(node_t));
    int right_array[2] = { 2, 1 };
    head->next = node1;
    node1->next = NULL;
    head->data = &right_array[0];
    node1->data = &right_array[1];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    fill_list("./unit_tests/data/three_elements.txt", &list, &arr);
    void *data = pop_back(&list);
    int rc = compare_lists(&node1, &list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(*(int*)data, 3);

    free_list(&list);
    free_list(&head);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE pop_back() TESTS
 */
START_TEST(test_pop_back_empty)
{
    node_t *list = NULL;
    node_t *new_list = pop_back(&list);
    ck_assert_ptr_null(new_list);
}
END_TEST

/*
 * NOTE: POSITIVE swap_edges() TESTS
 */
START_TEST(test_swap_edges)
{
    node_t *head = malloc(sizeof(node_t));
    node_t *node1 = malloc(sizeof(node_t));
    node_t *node2 = malloc(sizeof(node_t));
    int right_array[3] = { 3, 1, 2 };
    head->next = node1;
    node1->next = node2;
    node2->next = NULL;
    head->data = &right_array[0];
    node1->data = &right_array[1];
    node2->data = &right_array[2];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    fill_list("./unit_tests/data/three_elements.txt", &list, &arr);

    int rc = swap_edges(&list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    rc = compare_lists(&head, &list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&list);
    free_list(&head);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE swap_edges() TESTS
 */
START_TEST(test_swap_edges_empty_list)
{
    node_t *list = NULL;
    int rc = swap_edges(&list);
    ck_assert_int_eq(rc, EMPTY_LIST);
}
END_TEST

/*
 * NOTE: POSITIVE reverse() TESTS
 */
START_TEST(test_reverse)
{
    node_t *head = malloc(sizeof(node_t));
    node_t *node1 = malloc(sizeof(node_t));
    node_t *node2 = malloc(sizeof(node_t));
    int right_array[3] = { 3, 1, 2 };
    head->next = node1;
    node1->next = node2;
    node2->next = NULL;
    head->data = &right_array[0];
    node1->data = &right_array[1];
    node2->data = &right_array[2];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    fill_list("./unit_tests/data/three_elements.txt", &list, &arr);

    node_t *new_list = reverse(list);
    ck_assert_ptr_nonnull(new_list);

    int rc = compare_lists(&head, &new_list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&new_list);
    free_list(&head);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE reverse() TESTS
 */
START_TEST(test_reverse_empty_list)
{
    node_t *list = NULL;
    node_t *new_list = reverse(list);
    ck_assert_ptr_null(new_list);
}
END_TEST

/*
 * NOTE: POSITIVE sort_list() TESTS
 */
START_TEST(test_sort_list)
{
    node_t *head = malloc(sizeof(node_t));
    node_t *node1 = malloc(sizeof(node_t));
    node_t *node2 = malloc(sizeof(node_t));
    int right_array[3] = { 1, 2, 3 };
    head->next = node1;
    node1->next = node2;
    node2->next = NULL;
    head->data = &right_array[0];
    node1->data = &right_array[1];
    node2->data = &right_array[2];

    node_t *list = NULL;
    array_t arr = { .data = NULL, .len = 0 };
    fill_list("./unit_tests/data/three_elements.txt", &list, &arr);

    node_t *new_list = sort_list(&list, comparator);
    ck_assert_ptr_nonnull(new_list);

    int rc = compare_lists(&head, &new_list);
    ck_assert_int_eq(rc, EXIT_SUCCESS);

    free_list(&new_list);
    free_list(&head);
    free(arr.data);
}
END_TEST

/*
 * NOTE: NEGATIVE sort_list() TESTS
 */
START_TEST(test_sort_list_empty_list)
{
    node_t *list = NULL;
    node_t *new_list = sort_list(&list, comparator);
    ck_assert_ptr_null(new_list);
}
END_TEST

Suite *get_list_suite(void)
{
    Suite *suite = suite_create("files");
    TCase *tc_pos = tcase_create("Positives");
    tcase_add_test(tc_pos, test_fill_list_3);
    tcase_add_test(tc_pos, test_pop_front);
    tcase_add_test(tc_pos, test_pop_back);
    tcase_add_test(tc_pos, test_swap_edges);
    tcase_add_test(tc_pos, test_reverse);
    tcase_add_test(tc_pos, test_sort_list);
    suite_add_tcase(suite, tc_pos);

    TCase *tc_neg = tcase_create("Negatives");
    tcase_add_test(tc_neg, test_fill_list_one_element);
    tcase_add_test(tc_neg, test_pop_front_empty);
    tcase_add_test(tc_neg, test_pop_back_empty);
    tcase_add_test(tc_neg, test_swap_edges_empty_list);
    tcase_add_test(tc_neg, test_reverse_empty_list);
    tcase_add_test(tc_neg, test_sort_list_empty_list);
    suite_add_tcase(suite, tc_neg);

    return suite;
}
