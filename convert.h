#ifndef CS540_CONVERT_H
#define CS540_CONVERT_H

#include <stdbool.h>

#define BASE_MAX 20
#define BASE_MIN 2
#define BASE_STR "0123456789ABCDEFGHIJ"
#define BASE_MAX_LEN 32   //  Max length of the minimum base representation of INT_MAX

#define is_between(x, min, max) (x >= min && x <= max)

/*
  Converts a string of a given base to an integer.

  @param
    char *str: The string to convert
    int base : The base the number is represented in in the string

  @return
    An integer with the converted value or -1 on failure
*/
int stoi(char *str, unsigned int base);

/*
  Gets the index of a given value inside a string

  @param
    char *str: The string to search
    char value: The character to find in the string
    int occurance: Which occurance in the string to find (1 = first)

  @return
    The array index of the value or -1 if it was not found for the given occurance
*/
int get_index(char *str, char value, int occurance);

/*
  Converts an integer to a string representation of a given base

  @param
    int number: The number to convert
    int base: The base to convert to
    char *out: The location where the output string will be put (Must be pre-allocated)
    int max_len: The maximum length of the output buffer

  @return
    True if successful or false otherwise.
*/
bool itos(int number, int base, char *out, int max_len);

#endif
