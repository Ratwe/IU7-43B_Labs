#ifndef __EXPECTATION__H__
#define __EXPECTATION__H__

#include <stdio.h>

/**
 * @param[in]   input_file  File to get values
 * @param[out]  result      E(x) value
 * @return  Error code
 * @brief   Find expectation values from file
 */
int expectation_x(FILE *const input_file, double *result);

/**
 * @param[in]   input_file  File to get values
 * @param[out]  result      E(x*x) value
 * @return  Error code
 * @brief   Find expectation square values from file
 */
int expectation_sqr_x(FILE *const input_file, double *result);

#endif // #ifndef __EXPECTATION__H__
