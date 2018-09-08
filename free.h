#ifndef FREE_H
#define FREE_H

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

/**
 * Free memory if ptr is not NULL
 * 
 * Parameters
 * ----------
 * 
 * ptr
 *      Ptr to free
 * 
 * Example
 * -------
 * 
 *      char* ptr = malloc(1);
 *      if (ptr != NULL)
 *          free(ptr);
 * 
 *      // equivalent
 *      ptr = malloc(1);
 *      s_free(ptr);
 */
void s_free(void* ptr);

/**
 * Free 2D array ptr of given length if not NULL
 * 
 * Parameters
 * ----------
 * 
 * ptr
 *      2D array to free
 * 
 * Example
 * -------
 * 
 *      char** ptr = malloc(2);
 *      ptr[0] = malloc(100);
 *      ptr[1] = malloc(100);
 * 
 *      s_free_2D_array(ptr, 2);
 */
void s_free_2D_array(void** ptr, int length);

#endif