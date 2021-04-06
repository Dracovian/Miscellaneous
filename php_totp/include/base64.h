#ifndef __BASE64_H
#define __BASE64_H
#include "global.h"

int b64_length(int);
void b64_encode(const byte *, int, char *);

#endif // __BASE64_H
