#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "convert.h"

void usage()
{
  puts("Usage:");
  puts("\tconvert <number> <number's base> <base to go to>");
  puts("\tBase must be between 2 to 20 inclusive in base 10 format.");
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

  //  Convert the number string to uppercase which is what is used for bases over 10
  for (int i = 0; i < strlen(num_str); i++)
  {
    num_str[i] = toupper(num_str[i]);
  }

  //  Get the base 10 number from the string
  int number = stoi(num_str, num_base);

  //  If error (-1 return) then don't try to go any further
  if (number == -1)
  {
    return EXIT_FAILURE;
  }

  printf("The base 10 representation of %s is %d\n", num_str, number);

  getchar();

  return EXIT_SUCCESS;
}

int stoi(char *str, unsigned int base)
{
  char *range = BASE_STR;
  int length = strlen(str);
  int output = 0;

  //  Go through the string and see if it contains only valid characters
  for (int i = 0; i < length; i++)
  {
    //  If the current character is not within the valid choices
    if (strchr(range, str[i]) == NULL)
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
    if (strchr(str, range[i]) != NULL)
    {
      printf("The number %s is invalid for base %d: Found invalid character %c.\n", str, base, range[i]);
      return -1;
    }
  }


  for (int i = 0; i < length; i++)
  {
    int multiplier = (base * (length - i - 1));

    if (multiplier == 0)
    {
      multiplier = 1;
    }

    output += multiplier * get_index(range, str[i], 1);
  }

  return output;
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