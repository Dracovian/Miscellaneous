#ifndef BASE32_H
#define BASE32_H 1
#include <strfunc.h>

typedef struct {
    char *input;
    char output[0xFFFF];

} base32;

void b32_encode(base32 *);
void b32_decode(base32 *);

#endif