/*
 * compiler.h
 *
 * Dracovian <https://github.com/Dracovian>
 * May 8, 2020
 *
 * Determine which platform we're using.
 */

#ifndef __INC_COMPILER_H
#define __INC_COMPILER_H

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__) || defined(__MINGW32__) || defined(__MINGW32_MAJOR_VERSION) || \
    defined(__MINGW32_MINOR_VERSION) || defined(__MINGW64__) || defined (__MINGW64_MAJOR_VERSION) || \
    defined(__MINGW64_MINOR_VERSION) || defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSC_BUILD)

#ifdef PLATFORM_POSIX
#undef PLATFORM_POSIX
#endif

#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS
#endif

#else /* We're on a non-Windows platform */

#ifdef PLATFORM_WINDOWS
#undef PLATFORM_WINDOWS
#endif

#ifndef PLATFORM_POSIX
#define PLATFORM_POSIX
#endif

#endif /* Platform check */

#endif /* __INC_COMPILER_H */
