#include "variance.h"
#include "mean.h"

double echo_value(double value)
{
    return value;
}

double sqr_value(double value)
{
    return value * value;
}

int variance(FILE *input_file, double *result)
{
    int error_code;
    double exp_x, exp_sqr_x;

    error_code = function_mean(input_file, &echo_value, &exp_x);
    if (!error_code && !(error_code = function_mean(input_file, &sqr_value, &exp_sqr_x)))
        *result = exp_sqr_x - exp_x * exp_x;

    return error_code;
}
