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
  long int num_base = strtol(argv[2], NULL, 10);
  long int num_new_base = strtol(argv[3], NULL, 10);

  //  Check if given bases are within the correct values
  //  If strtol fails, it will return 0 which will be caught
  if (!is_between(num_base, BASE_MIN, BASE_MAX) || !is_between(num_new_base, BASE_MIN, BASE_MAX))
  {
    //  Print usage which tells them how to use the program correctly
    usage();
    return EXIT_FAILURE;
  }

  //  If the given bases are the same then warn the user
  //  This is a warning because testing can involve converting to the original base
  if (num_base == num_new_base)
  {
    puts("Warning: Number base and new base are equal.");
  }

  //  Convert the number string to uppercase which is what is used for bases over 10
  for (int i = 0; i < strlen(num_str); i++)
  {
    num_str[i] = toupper(num_str[i]);
  }

  //  Get the base 10 number from the string
  int number = stoi(num_str, num_base);

  //  printf("The base 10 representation of %s is %d\n", num_str, number);

  //  If error (-1 return) then don't try to go any further
  if (number == -1)
  {
    return EXIT_FAILURE;
  }


  //  Create a new string to hold the new base representation
  char *num_str_new = calloc(BASE_MAX_LEN, sizeof(char));

  //  Convert the number and store the output in num_str_new
  itos(number, num_new_base, num_str_new, BASE_MAX_LEN);

  //  Print the results
  printf("The base %d representation of %s (base %d) is %s\n", num_new_base, num_str, num_base, num_str_new);

  return EXIT_SUCCESS;
}

int stoi(char *str, unsigned int base)
{
  int length = strlen(str);
  int output = 0;

  //  Go through the string and see if it contains only valid characters
  for (int i = 0; i < length; i++)
  {
    //  If the current character is not within the valid choices
    if (strchr(BASE_STR, str[i]) == NULL)
    {
      printf("The number %s is invalid for base %d: Found invalid character %c.\n", str, base, str[i]);
      return -1;
    }
  }

  //  Start from the index of base which is always the start of invalid characters for the given base
  //  Go through each value past base and if it is found in the string then the given base is invalid
  for (int i = base; i < BASE_MAX; i++)
  {
    //  If the string has an invalid base character or 
    if (strchr(str, BASE_STR[i]) != NULL)
    {
      printf("The number %s is invalid for base %d: Found invalid character %c.\n", str, base, BASE_STR[i]);
      return -1;
    }
  }

  //  Go through each character in the string
  for (int i = 0; i < length; i++)
  {
    /*
      To represent base 10 numbers you have to successively multiply the value
      by 10 * the placement of the digit - 1. So 20 can be represented as (10^1 * 2) + (10^0 * 0)

      This is the same concept made dynamic for any given base.
    */
    int multiplier = pow(base, (length - i - 1)); //  Get base to the current digit's power

    //  If multiplier is 0 then we're on the last digit which is simply added
    if (multiplier == 0)
    {
      //  Prevent the number from turning into 0
      multiplier = 1;
    }

    output += multiplier * get_index(BASE_STR, str[i], 1);
  }

  return output;
}

bool itos(int number, int base, char *out, int max_len)
{
  int power = log(number) / log(base);  //  Get the maximum power of the number in the given base
  int i;

  for (i = 0; i < max_len - 1 && number > 0; i++, power--)
  {
    int amount = number / (int)pow(base, power);

    //  If this is the last number then just set the value
    if (power == 0)
    {
      amount = number;
      number = 0;
    }

    number -= (int)pow(base, power) * amount;

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

int get_index(char *str, char value, int occurance)
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