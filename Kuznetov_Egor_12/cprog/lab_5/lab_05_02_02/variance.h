#ifndef __VARIANCE__H__
#define __VARIANCE__H__

#include <stdio.h>

/**
 * @param[in]   input_file  Values file
 * @param[out]  result      D(x) value
 * @return  Error code
 * @brief   Find variance values from file
 */
int variance(FILE *input_file, double *result);

#endif // #ifndef __VARIANCE__H__
