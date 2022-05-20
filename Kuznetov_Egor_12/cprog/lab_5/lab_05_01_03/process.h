#ifndef __PROCESS__H__
#define __PROCESS__H__

#include <stdio.h> // Declare FILE struct

/**
 * @param[in]   f       File to process
 * @param[out]  count   Count sing changes
 * @return  Error code 
 * @breif   Process `f` file
 */
int process(FILE *f, int *count);

#endif // #ifndef __PROCESS__H__
