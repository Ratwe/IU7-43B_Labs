#ifndef __MEAN__H__
#define __MEAN__H__

#include <stdio.h>

/**
 * @param[in]   input_file  File to get values
 * @param[in]   edit_value  Function to edit input value
 * @param[out]  result      E(x) value
 * @return  Error code
 * @brief   Find expectation values from file
 */
int function_mean(FILE *const input_file, double (*edit_value)(double), double *result);

#endif // #ifndef __MEAN__H__
