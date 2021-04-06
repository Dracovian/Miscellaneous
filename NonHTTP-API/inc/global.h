#ifndef __API_H
#define __API_H

#include <malloc.h>
#include <string.h>

#ifdef __cplusplus
    #define INIT_EXTERN_C() extern "C" {
    #define EXIT_EXTERN_C() }
#else
    #define INIT_EXTERN_C()
    #define EXIT_EXTERN_C()
#endif

#ifdef USE_STATIC_FUNC
    #define API_FUNC static
#else
    #define API_FUNC
#endif

#endif // __API_H