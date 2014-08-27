#ifndef CS540_CONVERT_H
#define CS540_CONVERT_H

#include <stdint.h>
#include <stdbool.h>

#define BASE_MIN 2                        //  Minimum base that is valid to parse.
#define BASE_MAX 20                       //  Maximum base that is valid to parse
#define BASE_STR "0123456789ABCDEFGHIJ"   //  List of characters to use for a given base. Later characters go to higher bases.
#define BASE_MAX_LEN 33                   //  Max length of the minimum base representation of INT_MAX + 1 for NULL

//  Macro for checking if a number falls between two values (inclusive)
#define is_between(x, min, max) (x >= min && x <= max)

/*
  Converts a string of a given base to an integer.

  @param
    char *str: The string to convert
    uint32_t *number: Where to store the output number if the operation succeeds
    uint32_t base : The base the number is represented in in the string

  @return
    True if successful or false otherwise
*/
bool stoi(char *str, uint32_t *number, uint32_t base);

/*
  Converts an integer to a string representation of a given base

  @param
    uint32_t number: The number to convert
    uint32_t base: The base to convert to
    char *out: The location where the output string will be put (Must be pre-allocated)
    uint32_t max_len: The maximum length of the output buffer

  @return
    True if successful or false otherwise.
*/
bool itos(uint32_t number, uint32_t base, char *out, uint32_t max_len);

/*
  Gets the index of a given value inside of a string

  @param
    char *str: The string to search
    char value: The character to find in the string
    uint32_t occurance: Which occurance in the string to find (1 = first)

  @return
    The array index of the value or -1 if it was not found for the given occurance
*/
int32_t get_index(char *str, char value, uint32_t occurance);

#endif
