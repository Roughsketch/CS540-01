#ifndef CS540_CONVERT_H
#define CS540_CONVERT_H

#define BASE_MAX 20
#define BASE_MIN 2
#define BASE_STR "0123456789ABCDEFGHIJ"

#define is_between(x, min, max) (x >= min && x <= max)

//  String to Int
int stoi(char *str, unsigned int base);
int get_index(char *str, char value, int occurance);
void change_base(int n, int base, char *out, int max_len);

#endif
