#ifndef STRFUNC_H
#define STRFUNC_H 1

#include <stdlib.h>
#include <string.h>

#define ord(a) ((int)a)
#define chr(a,b) a[b]
#define len(a) strlen(a)

#define copy(a,b) strcpy(b,a)
#define cat(a,b) strcat(b,a)

int charpos(const char *, char);

#endif