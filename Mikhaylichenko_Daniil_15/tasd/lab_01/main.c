#include "functions.h"
#include "enter_functions.h"

int main(void)
{
    int rc;

    my_double first_num;

    rc = scan_my_double(&first_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    my_double second_num;

    rc = scan_my_int(&second_num);
    if (rc != EXIT_SUCCESS)
        return rc;

    my_double result;

    rc = divide(&first_num, &second_num, &result);
    if (rc != EXIT_SUCCESS)
        return rc;

    print_result(&result);

    return EXIT_SUCCESS;
}
