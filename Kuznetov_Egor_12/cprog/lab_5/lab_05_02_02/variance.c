#include "variance.h"
#include "expectation.h"

int variance(FILE *input_file, double *result)
{
    int error_code;
    double exp_x, exp_sqr_x;

    error_code = expectation_x(input_file, &exp_x);
    if (!error_code && !(error_code = expectation_sqr_x(input_file, &exp_sqr_x)))
        *result = exp_sqr_x - exp_x * exp_x;

    return error_code;
}
