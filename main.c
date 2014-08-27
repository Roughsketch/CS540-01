#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "convert.h"

void usage()
{
  puts("Usage:\tconvert <number> <number's base> <base to go to>");
  puts("\tNumber must be within the range of a signed integer.");
  printf("\tBase must be between %d to %d inclusive in decimal format.\n", BASE_MIN, BASE_MAX);
}

int main(int argc, char *argv[])
{
  //  If wrong number of arguments, assume they need help
  if (argc != 4)
  {
    usage();
    return EXIT_SUCCESS;
  }

  //  Get all the data we need from the command line
  char *num_str = argv[1];
  uint32_t num_base = strtol(argv[2], NULL, 10);
  uint32_t num_new_base = strtol(argv[3], NULL, 10);

  //  Check if given bases are within the correct values
  //  If strtol fails, it will return 0 which will be caught
  if (!is_between(num_base, BASE_MIN, BASE_MAX) || !is_between(num_new_base, BASE_MIN, BASE_MAX))
  {
    //  Print usage which tells them how to use the program correctly
    usage();
    return EXIT_FAILURE;
  }

  //  If the given bases are the same then tell the user
  if (num_base == num_new_base)
  {
    puts("Number base and new base are equal. Stopping.");
    return EXIT_SUCCESS;
  }

  //  Convert the number string to uppercase which is what is used for bases over 10
  for (uint32_t i = 0; i < strlen(num_str); i++)
  {
    num_str[i] = toupper(num_str[i]);
  }

  //  Get the base 10 number from the string
  uint32_t number = 0;

  if (!stoi(num_str, &number, num_base))
  {
    puts("Could not convert to base 10.");
    return EXIT_FAILURE;
  }

  printf("The base 10 representation of %s is %u\n", num_str, number);

  //  Create a new string to hold the new base representation
  char *num_str_new = calloc(BASE_MAX_LEN, sizeof(char));

  //  Convert the number and store the output in num_str_new
  if (!itos(number, num_new_base, num_str_new, BASE_MAX_LEN))
  {
    puts("Warning: itos returned false.");
  }

  //  Print the results
  printf("The base %u representation of %s (base %d) is %s\n", num_new_base, num_str, num_base, num_str_new);

  return EXIT_SUCCESS;
}

bool stoi(char *str, uint32_t *number, uint32_t base)
{
  uint32_t length = strlen(str);

  //  Go through the string and see if it contains only valid characters
  for (uint32_t i = 0; i < length; i++)
  {
    //  If the current character is not within the valid choices
    if (strchr(BASE_STR, str[i]) == NULL)
    {
      printf("The number %s is invalid for base %d: Found invalid character %c.\n", str, base, str[i]);
      return false;
    }
  }

  //  Start from the index of base which is always the start of invalid characters for the given base
  //  Go through each value past base and if it is found in the string then the given base is invalid
  for (uint32_t i = base; i < BASE_MAX; i++)
  {
    //  If the string has an invalid base character or 
    if (strchr(str, BASE_STR[i]) != NULL)
    {
      printf("The number %s is invalid for base %d: Found invalid character %c.\n", str, base, BASE_STR[i]);
      return false;
    }
  }

  //  Go through each character in the string
  for (uint32_t i = 0; i < length; i++)
  {
    /*
      To represent base 10 numbers you have to successively multiply the value
      by 10 * the placement of the digit - 1. So 20 can be represented as (10^1 * 2) + (10^0 * 0)

      This is the same concept made dynamic for any given base.
    */
    uint32_t multiplier = pow(base, (length - i - 1)); //  Get base to the current digit's power

    //  If multiplier is 0 then we're on the last digit which is simply added
    if (multiplier == 0)
    {
      //  Prevent the number from turning into 0
      multiplier = 1;
    }

    *number += multiplier * get_index(BASE_STR, str[i], 1);
  }

  return true;
}

bool itos(uint32_t number, uint32_t base, char *out, uint32_t max_len)
{
  int32_t power = log(number) / log(base);  //  Get the maximum power of the number in the given base
  uint32_t i;

  for (i = 0; i < max_len - 1 && number > 0; i++, power--)
  {
    uint32_t amount = number / (int)pow(base, power);

    //  If this is the last number then just set the value
    if (power == 0)
    {
      amount = number;
      //number = 0;
    }

    number -= (uint32_t)pow(base, power) * amount;

    out[i] = BASE_STR[amount];
  }

  //  For any remaining powers append a 0 to the string
  //  This is for cases like 0x64 -> 100d where it would try to return "1" instead of "100"
  for(;power >= 0; power--, i++)
  {
    out[i] = BASE_STR[0];
  }

  if (i >= max_len)
  {
    return false; //  Not enough space in the string
  }

  out[i] = '\0';  //  Null off the string because we're nice

  return true;  //  Success
}

int32_t get_index(char *str, char value, uint32_t occurance)
{
  char *ptr = NULL;

  //  Go through each occurance of value
  for(;occurance > 0; occurance--)
  {
    //  Find pointer to occurance
    ptr = strchr(str, value);

    //  If NULL then it was not found, return an invalid index
    if (ptr == NULL)
    {
      return -1;
    }
  }

  //  Return address of value minus the address of the base string
  return ptr - str;
}