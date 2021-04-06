#ifndef __LINKCRYPT_TYPES_H
#define __LINKCRYPT_TYPES_H

#undef UINT32_C
#undef INT64_C
#undef UINT64_C

#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT64_MIN

#undef INT8_MAX
#undef INT16_MAX
#undef INT32_MAX
#undef INT64_MAX

#undef UINT8_MIN
#undef UINT16_MIN
#undef UINT32_MIN
#undef UINT64_MIN

#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef UINT64_MAX

#undef INT_LEAST8_MIN
#undef INT_LEAST16_MIN
#undef INT_LEAST32_MIN
#undef INT_LEAST64_MIN

#undef INT_LEAST8_MAX
#undef INT_LEAST16_MAX
#undef INT_LEAST32_MAX
#undef INT_LEAST64_MAX

#undef UINT_LEAST8_MIN
#undef UINT_LEAST16_MIN
#undef UINT_LEAST32_MIN
#undef UINT_LEAST64_MIN

#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#undef UINT_LEAST32_MAX
#undef UINT_LEAST64_MAX

#undef INT_FAST8_MIN
#undef INT_FAST16_MIN
#undef INT_FAST32_MIN
#undef INT_FAST64_MIN

#undef INT_FAST8_MAX
#undef INT_FAST16_MAX
#undef INT_FAST32_MAX
#undef INT_FAST64_MAX

#undef UINT_FAST8_MIN
#undef UINT_FAST16_MIN
#undef UINT_FAST32_MIN
#undef UINT_FAST64_MIN

#undef UINT_FAST8_MAX
#undef UINT_FAST16_MAX
#undef UINT_FAST32_MAX
#undef UINT_FAST64_MAX

#undef INTPTR_MIN
#undef INTPTR_MAX
#undef UINTPTR_MIN
#undef UINTPTR_MAX

#undef INTMAX_MIN
#undef INTMAX_MAX
#undef UINTMAX_MIN
#undef UINTMAX_MAX

#undef INTMAX_WIDTH
#undef UINTMAX_WIDTH

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define CONCAT(a,b) a ## b
#define UINT32_C(c) CONCAT(c,U)

#undef __WORDSIZE
#undef __TIMESIZE

#if defined __x86_64__
    #if defined __ILP32__
        #define __WORDSIZE 32
        #define __TIMESIZE 64
    #else
        #define __WORDSIZE 64
        #define __TIMESIZE 64
    #endif
#else
    #define __WORDSIZE 32
    #define __TIMESIZE 32
#endif

/* Fixed-size types */
typedef signed char int8_t, int_least8_t, int_fast8_t;
typedef unsigned char uint8_t, uint_least8_t, uint_fast8_t;

typedef signed short int int16_t, int_least16_t;
typedef unsigned short int uint16_t, uint_least16_t;

typedef signed int int32_t, int_least32_t;
typedef unsigned int uint32_t, uint_least32_t;

#if __WORDSIZE == 64
    typedef signed long int int64_t, int_least64_t;
    typedef int64_t int_fast16_t, int_fast32_t, int_fast64_t;

    typedef unsigned long int uint64_t, uint_least64_t;
    typedef uint64_t uint_fast16_t, uint_fast32_t, uint_fast64_t;

    typedef int64_t intptr_t;
    typedef uint64_t uintptr_t;

    #define INT64_C(c) CONCAT(c, L)
    #define UINT64_C(c) CONCAT(c, UL)
#else
    typedef signed long long int int64_t, int_least64_t;
    typedef unsigned long long int uint64_t, uint_least64_t;

    typedef int32_t int_fast16_t, int_fast32_t;
    typedef uint32_t uint_fast16_t, uint_fast32_t;

    typedef int32_t intptr_t;
    typedef uint32_t uintptr_t;

    #define INT64_C(c) CONCAT(c, LL)
    #define UINT64_C(c) CONCAT(c, ULL)
#endif

/* Limits of integral types */
#define INT8_MIN  (~0x7F)
#define INT16_MIN (~0x7FFF)
#define INT32_MIN (~0x7FFFFFFF)
#define INT64_MIN (INT64_C(~0x7FFFFFFFFFFFFFFF))

#define INT8_MAX  (0x7F)
#define INT16_MAX (0x7FFF)
#define INT32_MAX (0x7FFFFFFF)
#define INT64_MAX (INT64_C(0x7FFFFFFFFFFFFFFF))

#define UINT8_MIN  (0)
#define UINT16_MIN (0)
#define UINT32_MIN (0)
#define UINT64_MIN (0)

#define UINT8_MAX  (0xFF)
#define UINT16_MAX (0xFFFF)
#define UINT32_MAX (UINT32_C(0xFFFFFFFF))
#define UINT64_MAX (UINT64_C(0xFFFFFFFFFFFFFFFF))

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN

#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX

#define UINT_LEAST8_MIN  (0)
#define UINT_LEAST16_MIN (0)
#define UINT_LEAST32_MIN (0)
#define UINT_LEAST64_MIN (0)

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INT_FAST8_MIN INT8_MIN
#define UINT_FAST8_MIN UINT8_MIN

#if __WORDSIZE == 64
    #define INT_FAST16_MIN INT64_MIN
    #define INT_FAST32_MIN INT64_MIN
    #define INT_FAST64_MIN INT64_MIN

    #define INT_FAST16_MAX INT64_MAX
    #define INT_FAST32_MAX INT64_MAX
    #define INT_FAST64_MAX INT64_MAX

    #define UINT_FAST64_MIN (0)

    #define UINT_FAST16_MAX UINT64_MAX
    #define UINT_FAST32_MAX UINT64_MAX
    #define UINT_FAST64_MAX UINT64_MAX

    #define INTPTR_MIN INT64_MIN
    #define INTPTR_MAX INT64_MAX
    #define UINTPTR_MAX UINT64_MAX

    #define INTMAX_MIN INT64_MIN
    #define INTMAX_MAX INT64_MAX
    #define UINTMAX_MAX UINT64_MAX
#else
    #define INT_FAST16_MIN INT32_MIN
    #define INT_FAST32_MIN INT32_MIN

    #define INT_FAST16_MAX INT32_MAX
    #define INT_FAST32_MAX INT32_MAX

    #define UINT_FAST16_MAX UINT32_MAX
    #define UINT_FAST32_MAX UINT32_MAX

    #define INTPTR_MIN INT32_MIN
    #define INTPTR_MAX INT32_MAX
    #define UINTPTR_MAX UINT32_MAX

    #define INTMAX_MIN INT32_MIN
    #define INTMAX_MAX INT32_MAX
    #define UINTMAX_MAX UINT32_MAX
#endif

#define UINT_FAST16_MIN (0)
#define UINT_FAST32_MIN (0)
#define UINTPTR_MIN (0)
#define UINTMAX_MIN (0)

/* Define bit widths for each type */
#define INT8_WIDTH  8
#define INT16_WIDTH 16
#define INT32_WIDTH 32
#define INT64_WIDTH 64

#define UINT8_WIDTH  8
#define UINT16_WIDTH 16
#define UINT32_WIDTH 32
#define UINT64_WIDTH 64

#define INT_LEAST8_WIDTH  8
#define INT_LEAST16_WIDTH 16
#define INT_LEAST32_WIDTH 32
#define INT_LEAST64_WIDTH 64

#define UINT_LEAST8_WIDTH  8
#define UINT_LEAST16_WIDTH 16
#define UINT_LEAST32_WIDTH 32
#define UINT_LEAST64_WIDTH 64

#define INT_FAST8_WIDTH  8
#define INT_FAST16_WIDTH __WORDSIZE
#define INT_FAST32_WIDTH __WORDSIZE
#define INT_FAST64_WIDTH 64

#define UINT_FAST8_WIDTH  8
#define UINT_FAST16_WIDTH __WORDSIZE
#define UINT_FAST32_WIDTH __WORDSIZE
#define UINT_FAST64_WIDTH 64

#define INTPTR_WIDTH  __WORDSIZE
#define UINTPTR_WIDTH __WORDSIZE
#define INTMAX_WIDTH  __WORDSIZE
#define UINTMAX_WIDTH __WORDSIZE

/* Arbitrary Precision */
typedef unsigned uint128_t __attribute__((mode(TI)));
#define INT128_CONSTANT(hi,lo) ((((uint128_t) hi) << 64) + lo)

typedef uint64_t uint256_t __attribute__((__vector_size__(32)));
typedef uint64_t uint512_t __attribute__((__vector_size__(64)));

#endif