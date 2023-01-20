#include "../inc/unit_tests.h"

int nodecmp(node_t *first, node_t *second)
{
    if (first->num == second->num && first->power == second->power)
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}

int compare_lists(node_t **first, node_t **second)
{
    node_t *cur1 = *first, *cur2 = *second;

    for (; cur1->next && cur2->next; cur1 = cur1->next, cur2 = cur2->next)
        if (nodecmp(cur1, cur2) != EXIT_SUCCESS)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int main(void)
{
    Suite *output_suite = get_output_suite();
    Suite *list_suite = get_list_suite();
    Suite *process_suite = get_process_suite();

    SRunner *runner = srunner_create(output_suite);
    srunner_add_suite(runner, list_suite);
    srunner_add_suite(runner, process_suite);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_VERBOSE);
    int total_failure = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (!total_failure) ? EXIT_SUCCESS : EXIT_FAILURE;
}

