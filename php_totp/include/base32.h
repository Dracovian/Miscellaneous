#ifndef __BASE32_H
#define __BASE32_H
#include "global.h"

int get_length(int);
void pad_input(char *, int);

int get_octet(int);
int get_offset(int);

char shift_right(char, int);
char shift_left(char, int);

char encode_char(char);
int  decode_char(char);

int  decode_sequence(const char *, char *);
void encode_sequence(const char *, int, char *);

void b32_encode(const char *, int, char *);
int  b32_decode(const char *, char *);

#endif // __BASE32_H
