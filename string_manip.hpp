#ifndef STRING_MANIP_HPP
#define STRING_MANIP_HPP

#include <vector>
#include <iostream>
#include <cstring>
#include <sstream>
#include <utility>

#include "dbg.hpp"

/** Splits the given str string using the given
 * delimiter. A vector of string is returned,
 * containing for each element a token of the
 * string.
 *
 * Parameters
 * ----------
 * str
 *      String to split
 * delimiter
 *      Character seperating the tokens
 *
 * Return value
 * ------------
 *
 * The vector containing the tokens is returned.
 *
 * Example
 * -------
 *
 *      string text = "I'm a text";
 *
 *      cout << "Text: " << text << endl;
 *      cout << "explode: " << endl;
 *      vector<string> tokenList = explode(text, ' ');
 *      for(string str : tokenList) {
 *          cout << str << endl;
 *      }
 *
 * output:
 * Text: I'm a text
 * explode:
 * I'm
 * a
 * text
 */
std::vector<std::string> explode(const std::string& str, char delimiter);

/** Splits the given str string using the given
 * delimiters. A vector of string is returned,
 * containing for each element a token of the
 * string.
 *
 * Parameters
 * ----------
 * str
 *      String to split
 * delimiters
 *      String representing characters that will be
 *      considered as separators. Each character from
 *      delim will be a single separator. For splitting
 *      with a whole string delimiter, check explode_subtring.
 *
 * Return value
 * ------------
 *
 * The vector containing the tokens is returned.
 *
 * Example
 * -------
 *
 *      string text = "I'm a,text.and_thats!it";
 *
 *      cout << "Text: " << text << endl;
 *      cout << "explode: " << endl;
 *      vector<string> tokenList = explode(text, " ,._!");
 *      for(string str : tokenList) {
 *          cout << str << endl;
 *      }
 *
 * output:
 * Text: I'm a,text.and_that's!it
 * explode:
 * I'm
 * a
 * text
 * and
 * that's
 * it
 */
std::vector<std::string> explode(const std::string& str, const std::string& delimiters = " ");

/** Splits the given str string using the given
 * delimiter string. A vector of string is returned,
 * containing for each element a token of the
 * string.
 *
 * Parameters
 * ----------
 * str
 *      String to split
 * delimiter_string
 *      The string that will be used to split str. The whole
 *      string must appear to be considered as a delimiter. For
 *      splitting with multiple different delimiters, check
 *      the function explode.
 *
 * Return value
 * ------------
 *
 * The vector containing the tokens is returned.
 *
 * Example
 * -------
 *
 *      string text = "I'm  a text";
 *
 *      cout << "Text: " << text << endl;
 *      cout << "explode: " << endl;
 *      vector<string> tokenList = explode(text, "  ");
 *      for(string str : tokenList) {
 *          cout << str << endl;
 *      }
 *
 * output:
 * Text: I'm  a text
 * explode:
 * I'm
 * a text
 */
std::vector<std::string> explode_substring(const std::string& str, const std::string& delimiter_substr);

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
 *      string str = " text ";
 *      string trimmed = remove_whitespaces(str);
 *      cout << trimmed;
 *
 * output:
 * text
 *
 */
std::string trim_whitespaces(std::string str);

#endif
