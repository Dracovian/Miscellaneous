#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define MIN(X,Y) ((X)>(Y)?(Y):(X))

#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

typedef unsigned char byte;

typedef short     i16;
typedef int       i32;
typedef long long i64;

typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define CHAR_MIN 0x80
#define CHAR_MAX 0x7F
#define BYTE_MAX 0xFF

#define I16_MIN  0x8000
#define I16_MAX  0x7FFF
#define U16_MAX  0xFFFF

#define I32_MIN  0x80000000
#define I32_MAX  0x7FFFFFFF
#define U32_MAX  0xFFFFFFFF

#define I64_MIN  0x8000000000000000
#define I64_MAX  0x7FFFFFFFFFFFFFFF
#define U64_MAX  0xFFFFFFFFFFFFFFFF 

#endif // __GLOBAL_H
