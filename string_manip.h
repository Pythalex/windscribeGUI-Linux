#ifndef STRING_MANIP_H
#define STRING_MANIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg.h"

/**
 * Splits the given str string using the given
 * delimiters delim. A 2D string array is returned,
 * containing for each element a token of the
 * string.
 * 
 * Parameters
 * ----------
 * str
 *      C String to split
 * delimchar
 *      C String representing characters that will be
 *      considered as separators. Each character from
 *      delim will be a single separator.
 * 
 * length_ptr
 *      Int pointer, receives the splitted array length.
 * 
 * 
 * Return value
 * ------------
 * 
 * The splitted 2D string array is returned.
 * If the splitting fails, NULL is returned.
 * 
 * Example
 * -------
 * 
 *      char text[] = "I'm a text";
 *      char** splitted;
 *      int size = 0;
 *      splitted = split_str(text, " ", &size);
 * 
 *      for (int i = 0; i < size; i++)
 *          printf("%s\n", splitted[i]);
 * 
 * output:
 * I'm
 * a
 * text
 * 
 * 
 *      char text[] = "I'm,a.text";
 *      char** splitted;
 *      int size = 0;
 *      splitted = split_str(text, ".,", &size);
 * 
 *      for (int i = 0; i < size; i++)
 *          printf("%s\n", splitted[i]);
 * 
 * output:
 * I'm
 * a
 * text
 */
char** split_str(const char* str, const char* delim, int* length_ptr);

/**
 * Splits the given str string using the given
 * delimiter substring delim_substr. 
 * A 2D string array is returned,
 * containing for each element a token of the
 * string. If a token is an empty character (e.g. if str
 * contains two contiguous delim_substr), it's not added
 * to the splitted array.
 * 
 * Parameters
 * ----------
 * str
 *      C String to split
 * 
 * delim_substr
 *      C String representing characters that will be
 *      considered as separator substring.
 * 
 * length_ptr
 *      Int pointer, receives the splitted array length.
 * 
 * 
 * Return value
 * ------------
 * 
 * The splitted 2D string array is returned.
 * If the splitting fails, NULL is returned.
 * 
 * Example
 * -------
 * 
 *      char text[] = "I'm a  text   a";
 *      int length = 0;
 *      char** splitted = split_str_substring(text, "  ", &length);
 * 
 *      for (int i = 0; i < length; i++){
 *          printf("%s\n", splitted[i]);
 *      }
 * 
 * output:
 * I'm a
 * text
 *  a
 * 
 *      char text[] = "I'm a  text    a";
 *      int length = 0;
 *      char** splitted = split_str_substring(text, "  ", &length);
 * 
 *      for (int i = 0; i < length; i++){
 *          printf("%s\n", splitted[i]);
 *      }
 * 
 * output:
 * I'm a
 * text
 * a
 */
char** split_str_substring(const char* str, const char* delim_substr, 
    int* length_ptr);


/**
 * Trims the string to remove leading and trailing whitespaces.
 * 
 * Parameters
 * ----------
 * 
 * str
 *      The string to trim.
 * 
 * Return value
 * --------------
 * 
 * Returns a new string with no leading or trailing whitespaces.
 * 
 * Example
 * -------
 * 
 *      const char* str = " text ";
 *      char* newstr = remove_whitespaces(str);
 *      printf("%s", newstr);
 * 
 * output:
 * text
 * 
 */
char* remove_whitespaces(const char* string);

#endif